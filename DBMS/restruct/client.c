/*************************************************************************
	> File Name: client.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年12月21日 星期日 22时10分24秒
 ************************************************************************/
#include "client.h"
#define MAX_SIZE 4096
#define MASTER_PORT 8080
#define MASTER_ADDR "10.181.71.96"
#define CLIENT_PORT 8888
#define NUM 3

char *get_conf_value(char *path_name, char *key_name, char *value);
int socket_create(int port);
void *func(void *arg);
void *heart(void *arg);

pthread_mutex_t mut[NUM];
char log_files[NUM][20] = {"cpu.log", "disk.log", "memory.log"};
char script_files[NUM][50] = {"bash ./sysinfo/check_cpu.sh", "bash ./sysinfo/check_memory.sh", "bash ./sysinfo/disk.sh"};
int interval[NUM] = {5, 10, 10};

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
    // 开启NUM个线程
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
    while (1) {
        
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
        dest_addr.sin_addr.s_addr = inet.addr(MASTER_ADDR);
        if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
            perror("heart connect");
            exit(1);
        }
        close(sockfd);
        sleep(3);                                   // 每隔一段时间发送一次心跳
    }
}
void *func(void *arg) {
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
        printf("open %s\n", log_path);
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

