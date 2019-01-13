/*************************************************************************
	> File Name: client.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年12月21日 星期日 22时10分24秒
 ************************************************************************/
#include "client.h"
#define MAX_SIZE 4096
#define MASTER_PORT 8080
#define MASTER_ADDR "127.0.0.1"
#define CLIENT_PORT 8888
#define NUM 3

char *get_conf_value(char *path_name, char *key_name, char *value);
int socket_create(int port);
void *func(void *arg);
void *heart(void *arg);

pthread_mutex_t mut[NUM];
char log_files[NUM][20] = {"cpu.log", "disk.log", "memory.log"};
char script_files[NUM][50] = {"bash ./sysinfo/check_cpu.sh", "bash ./sysinfo/check_memory.sh", "bash ./sysinfo/disk.sh"};
int interval[NUM] = {5, 10, 10};                        // 每个脚本执行的时间间隔

int main(int argc, char *argv[]) {
    pthread_t t[NUM + 1], t_heart;
    mypara para[NUM + 1];
    // 创建心跳线程
    if (pthread_create(&t_heart, NULL, heart, NULL) == -1) {
        perror("create heart pthread");
    }
    // 初始化互斥锁
    for (int i = 0; i < NUM; i++) {
        pthread_mutex_init(&mut[i], NULL);
    }
    // 开启NUM个线程,每个线程执行一个脚本
    // 先开启3个, 后续开启6个
    for (int i = 0 ; i < NUM; i++) {
        para[i].num = i;
        if (pthread_create(&t[i], NULL, func, (void *)&para[i]) == -1) {
            perror("create pthread");
            return -1;
        }
    }
    // 主线程的任务
    // TODO:接收master端的要求,建立连接发送日志文件
    /** 
     * master端线程取出对应工作队列中的主机
     * 尝试连接,如果连接上,则此为长连接
     * 依次发送100~100+NUM,分别表示要求不同的脚本信息
     * client收到后回复200~200+NUM,表示存在相应的日志文件
     * master端线程收到回复后建立短连接到client,client开放端口为CLIENT_PORT:8888
     * client接受连接后,将文件发送给master端,之后短连接关闭,此过程注意加互斥锁,因为读的同时其他线程在写
     * master端的长连接也关闭
     * 循环以上过程
    **/
    // TODO:发送报警信息
    int listen_sock = socket_create(CLIENT_PORT), confd;
    while (1) {
        struct sockaddr_in master_addr;
        socklen_t len = sizeof(master_addr);
        if ((confd = accept(listen_sock, (struct sockaddr*)&master_addr, &len)) == -1) {
            perror("accept");
            return -1;
        }
        char *temp = inet_ntoa(master_addr.sin_addr);
        printf("receive connect from master:%s\n", temp);
        
        // master连接后, 进行收发日志文件
        int code;
        while (1) { 
            if (recv(confd, &code, 4, 0) <= 0) break;
            char filename[20] = "./Log/";
            strcat(filename, log_files[code - 100]);
            printf("code: %d, file: %s\n", code, filename);
            if (access(filename, 0)) {
                perror("file not exist!");
                exit(0);                        // 返回400?
            } else {
                // 存在此文件,则建立连接进行收发数据
                code += 100;
                send(confd, &code, 4, 0);               // 返回200
                int data_confd;                         // 短连接(数据连接)
                struct sockaddr_in data_addr;           
                int len = sizeof(data_addr);
                if ((data_confd = accept(listen_sock, (struct sockaddr*)&data_addr, &len)) == -1) {
                    perror("data accept");
                    return -1;
                }
                printf("begin send sysinfo %d to %s\n", code, inet_ntoa(data_addr.sin_addr));
                char buf[MAX_SIZE + 1] = {0};
                pthread_mutex_lock(&mut[code - 200]);
                FILE *fp = fopen(filename, "r");
                while (fread(buf, 1, MAX_SIZE, fp) > 0) {
                    buf[MAX_SIZE] = '\0';
                    send(data_confd, buf, strlen(buf), 0);
                    printf("data:%s\n", buf);
                    memset(buf, 0, sizeof(buf));
                }
                fclose(fp);
                // 日志文件传送完毕后即删除
                char del_command[50] = {0};         
                sprintf(del_command, "%s > %s", "", filename);
                system(del_command);
                pthread_mutex_unlock(&mut[code - 200]);
                close(data_confd);
            }
        }   // 收发文件
        close(confd);       // 传输完毕断开长连接
    }

    
    return 0;
}
void *heart(void *arg) {
    while (1) {
        int sockfd;
        struct sockaddr_in dest_addr;
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("heart socket create");
            exit(1);
        }
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(MASTER_PORT);
        dest_addr.sin_addr.s_addr = inet_addr(MASTER_ADDR);
        if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
            perror("heart connect");
        }
        close(sockfd);
        sleep(5);                                   // 每隔一段时间发送一次心跳
    }
}
void *func(void *arg) {                             // 执行相应的脚本
    mypara *para = (mypara *)arg;
    char buffer[MAX_SIZE + 1] = {0};
    int id = para->num;
    while (1) {
        printf("pthread %d run %s\n", id, script_files[id]);
        FILE *pp;
        if ((pp = popen(script_files[id], "r")) == NULL) {
            perror("shell script popen");
            exit(1);
        }
        char log_path[50] = "./Log";
        if (NULL == opendir(log_path)) {
            mkdir(log_path, 0777);
        }
        strcat(log_path, "/");
        strcat(log_path, log_files[id]);
        printf("write %s\n", log_path);
        pthread_mutex_lock(&mut[id]);
        FILE *fp = fopen(log_path, "a+");
        while (fread(buffer, 1, MAX_SIZE, pp) > 0) {
            buffer[MAX_SIZE] = '\0';
            fwrite(buffer, 1, strlen(buffer), fp);
            memset(buffer, 0, sizeof(buffer));
        }
        fclose(pp);
        fclose(fp);
        pthread_mutex_unlock(&mut[id]);
        sleep(interval[id]);                                //每个脚本的执行间隔时间不同
    }
}
char *get_conf_value(char *path_name, char *key_name, char *value) {
    FILE *fp = fopen(path_name, "r");
    if (fp == NULL) {
        perror("error open file");
        exit(0);
    }
    int read_cnt;
    char *line = NULL;
    size_t len = 0;
    while ((read_cnt = getline(&line, &len, fp)) != -1) {
        int lenb = strlen(key_name);
        value = strstr(line, key_name);  //如果找不到子串则返回NULL
        if (value == NULL) continue;     //找到则返回第一次出现的位置 
        value = value + lenb + 1;        //额外加1用来跳过'='号
        //printf("%s is %s", key_name, value);
        //　找到后就break这样可以得到正确的value
        break;
    }
    return value;
}
int socket_create(int port) {
    int socket_server, sockfd;
    struct sockaddr_in s_addr, c_addr;
    socklen_t len;
    if ((socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                perror("socket create");
                return -1;
            
    }
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    //printf("port:%d\n", s_addr.sin_port);
    s_addr.sin_addr.s_addr = htons(INADDR_ANY);
    
    // 端口复用
    int opt = 1;
    setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));

    if ((bind(socket_server, (struct sockaddr*)&s_addr, sizeof(struct sockaddr))) < 0) {
                perror("bind");
                return -1;
            
    }
    if (listen(socket_server, 10) < 0) {
                perror("listen");
                return -1;
            
    }
    return socket_server;
}

