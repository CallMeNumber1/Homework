/*************************************************************************
	> File Name: master.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年12月23日 星期日 09时10分50秒
 ************************************************************************/

#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>

// 最多设置的线程数
#define INS 5
#define PORT 8080
#define CLIENT_PORT 8888
#define MAX_SIZE 4096
#define NUM 3
#define WARN_PORT 5555
pthread_mutex_t mut[NUM];
typedef struct mypara {
    char *s;
    //　传入参数标志是哪个线程
    int num;
} mypara;

typedef struct Node {
    struct sockaddr_in addr;
    int sockfd;
    struct Node *next;
} Node, *LinkedList;

int queue[INS + 1] = {0};
LinkedList linkedlist[INS + 1];

Node insert(Node *head, char *ip_str, int sockfd) {
    printf("\033[32m-----Insert begining-----\033[0m\n");
    printf("insert %s success\n", ip_str);
    // 封装sockaddr_in结构体
    struct sockaddr_in t_addr;
    t_addr.sin_family = AF_INET;
    t_addr.sin_port = htons(CLIENT_PORT);              // client端监听的端口
    t_addr.sin_addr.s_addr = inet_addr(ip_str);
    Node ret;
    ret.next = head;
    Node *p = (Node *)malloc(sizeof(Node));
    p->addr = t_addr;p->sockfd = sockfd;
    p->next = ret.next;
    ret.next = p;
    return ret;
}

void output(Node *head) {
    Node *p = head;
    printf("[ ");
    while (p) {
        printf("%s:%d ", inet_ntoa(p->addr.sin_addr), p->addr.sin_port);
        p = p->next;
    }
    printf("]\n");

}
void output2(Node *head, int num) {
    Node *p = head;
    //char logfile[20];
    //sprintf(logfile, "%d.log", num);
    ///FILE *log = fopen(logfile, "a+");
    printf("\033[33m-----queue[%d]:%d个元素-----\033[0m", num, queue[num]);
    printf("[ ");
    //fprintf(log, "[ ");
    while (p) {
        printf("%s:%d ", inet_ntoa(p->addr.sin_addr), p->addr.sin_port);
        //fprintf(log, "%s:%d ", inet_ntoa(p->addr.sin_addr), p->addr.sin_port);
        p = p->next;
    }
    printf("]\n");
    //fprintf(log, "]\n");
}
// 传出的是最小的下标，而非最小值!!!!!!
int find_min(int n, int *arr) {
    int min = 100, ind = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
            ind = i;
        } 
    }
    return ind;
}
void *func(void *arg);
void *warn_func(void *arg);
int socket_create(int port);
char *get_conf_value(char *path_name, char *key_name, char *value);
// 检查是否已存在这个IP
int isrepeat(struct sockaddr_in new) {
    int flag = 0;
    for (int i = 0; i < INS && !flag; i++) {
        Node *p = linkedlist[i];
        while (p && !flag) {
            if (new.sin_addr.s_addr == p->addr.sin_addr.s_addr) flag = 1;
            p = p->next;
        }
    }
    return flag;
}
Node delete_node(Node *head, int len, struct sockaddr_in old);
int main() {
    for (int i = 0; i < NUM; i++) {
        pthread_mutex_init(&mut[i], NULL);
    }
    // 初始化链表数组
    for (int i = 0; i <= INS; i++) {
        linkedlist[i] = NULL;
    }
    pthread_t t[INS + 1];
    mypara para[INS + 1];
     
    // 从配置文件中读取初始化信息
    char value[20];
    char *prename = get_conf_value("./init.conf", "prename", value);
    char *start = get_conf_value("./init.conf", "start", value);
    char *finish = get_conf_value("./init.conf", "finish", value);
    /*   
    for (int i = atoi(start); i <= atoi(finish); i++) {
        char temp[20];
        strcpy(temp, prename);
        // 不减1,则拼接时会有换行
        sprintf(temp + strlen(temp) - 1, ".%d", i);
        // 选择元素较少的链表插入,均衡线程间的负载
        int ind = find_min(INS, queue);
        Node ret;
        ret = insert(linkedlist[ind], temp, 0);
        linkedlist[ind] = ret.next;
        queue[ind]++;
    }
    */

    // 用来接受报警信息的线程
    pthread_t warn;                                       
    if (pthread_create(&warn, NULL, warn_func, NULL) == -1) {
        perror("warn pthread create");
        exit(1);
    }


    for (int i = 0; i < INS; i++) {
        // 设置num的值后将para传入任务，可用来标识线程
        para[i].num = i; 
        //para[i].s = "Hello HaiZei!";
        pthread_create(&t[i], NULL, func, (void *)&para[i]);
        printf("Current pthread id = %ld \n", t[i]);
    }
   
    for (int i = 0; i < INS; i++) {
        printf("%d ", queue[i]);
        printf(" ....... ");
        output(linkedlist[i]);
    }

    int server_socket = socket_create(8080);
    int confd;
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        if ((confd = accept(server_socket, (struct sockaddr*)&client_addr, &len)) == -1) {
            perror("accept");
            return -1;
        }
        //printf("%s connection\n", inet_ntoa(client_addr.sin_addr));
        char *temp = inet_ntoa(client_addr.sin_addr);
        if (isrepeat(client_addr)) {
            printf("Exist client!\n");
            continue;
        }
        // 将client_addr插入链表
        // 选择元素较少的链表插入,均衡线程间的负载
        int ind = find_min(INS, queue);
        Node ret;
        pthread_mutex_lock(&mut[ind]);
        ret = insert(linkedlist[ind], temp, confd);
        linkedlist[ind] = ret.next;
        queue[ind]++;
        pthread_mutex_unlock(&mut[ind]);
        for (int i = 0; i < INS; i++) {
            printf("%d ", queue[i]);
            printf(" ....... ");
            output(linkedlist[i]);
        }
        sleep(3);
        for (int i = 0; i < INS; i++) {
            printf("%d ", queue[i]);
            printf(" ....... ");
            output(linkedlist[i]);
        }
    }
    //　先让子进程执行完毕
    pthread_join(t[0], NULL); //等待当前执行的线程完毕
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);
    pthread_join(t[4], NULL);
   
    return 0;
}
void *warn_func(void *arg) {
    int warn_listen = socket_create(WARN_PORT);
    int warn_confd;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    while (1) {
        if ((warn_confd = accept(warn_listen, (struct sockaddr*)&client_addr, &len)) < 0) {
            perror("warn accept");
            continue;
        }
        char filename[50] = "./Log/warning";
        strcat(filename, inet_ntoa(client_addr.sin_addr));
        if (NULL == opendir(filename)) {
            mkdir(filename, 0777);
        }
        strcat(filename, "/cpu.log");
        FILE *fp = fopen(filename, "a+");
        if (fp == NULL) {
            perror("error opening file");
            exit(0);
        }
        int len = 0; char buffer[MAX_SIZE + 1] = {0};
        while ((len = recv(warn_confd, buffer, MAX_SIZE, 0)) > 0) {
            buffer[len] = '\0';
            fflush(stdout);
            fwrite(buffer, 1, len, fp);
            memset(buffer, 0, sizeof(buffer));                
        }
        fclose(fp);
        close(warn_confd);
    }
    close(warn_listen);
    return NULL;
}
Node delete_node(Node *head, int para_num, struct sockaddr_in old) {
    printf("\033[31m-----Delete begining-----\033[0m\n");
    Node ret, *p;
    ret.next = head;
    p = &ret;
    printf("delete %s success\n", inet_ntoa(old.sin_addr));
    if (queue[para_num] == 1) {
        ret.next = NULL;
    } else {
        while (p->next->addr.sin_addr.s_addr != old.sin_addr.s_addr && p) {
            p = p->next;
        }
        p->next = p->next->next;
    }
    return ret;
}
void *func(void *arg) {
    mypara *para = (mypara *)arg;
    while (1) {
        Node *p = linkedlist[para->num];
        if (p == NULL) {
            printf("pthread %d job queue empty, sleep\n", para->num);
            sleep(5);
            //continue;
        }
        while (p) {
            // 先判断client是否还活着
            int client_sockfd = p->sockfd, byte;
            int sockfd;
            if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                perror("Socket");
                exit(0);
            }
            // 连接client
            if (connect(sockfd, (struct sockaddr *)&p->addr, sizeof(p->addr)) < 0) {
                perror("connect");
                //printf("sockfd = %d\n", sockfd);
                pthread_mutex_lock(&mut[para->num]);
                Node ret = delete_node(linkedlist[para->num], para->num, p->addr);
                linkedlist[para->num] = ret.next;
                queue[para->num]--;
                printf("queue[%d]剩余 %d 个元素\n", para->num, queue[para->num]);
                pthread_mutex_unlock(&mut[para->num]);
                output2(linkedlist[para->num], para->num);
            } else {
                sleep(2);
                // 100代表cpu, 101代表内存, 102代表磁盘
                char log_files[NUM][50] = {"/cpu.log", "/mem.log", "/disk.log"};
                for (int i = 100; i < 100 + NUM; i++) {
                    send(sockfd, &i, 4, 0);
                    int len, code;
                    if ((len = recv(sockfd, &code, 4, 0)) > 0) {
                        if (code >= 200) {                 // 收到返回值200,主动连接client
                            printf("ready to accept info %s\n", log_files[code - 200]);
                            int data_sockfd;
                            if ((data_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                                perror("data socket");
                                exit(0);
                            }
                            // 与client建立连接
                            struct sockaddr_in temp_addr = p->addr;
                            if (connect(data_sockfd, (struct sockaddr *)&temp_addr, sizeof(temp_addr)) < 0) {
                                perror("data connect");
                                exit(0);
                            } else {
                                printf("connection built! recv begins!\n");
                                // 创建文件夹 对收到的client日志进行处理(保存)
                                char filename[100] = "/home/chongh/Homework/DBMS/restruct/";
                                strcat(filename, inet_ntoa(temp_addr.sin_addr));
                                if (NULL == opendir(filename)) {
                                    mkdir(filename, 0777);
                                }
                                strcat(filename, log_files[code - 200]);
                                pthread_mutex_lock(&mut[para->num]);
                                FILE *fp;
                                if ((fp = fopen(filename, "a+")) == NULL) {
                                    perror("error opening file");
                                    exit(0);
                                }
                                int len = 0; char buf[MAX_SIZE + 1] = {0};
                                while ((len = recv(data_sockfd, buf, MAX_SIZE, 0)) > 0) {
                                    buf[len] = '\0';
                                    printf("%s:%d : recv %d 字节 %s\n", inet_ntoa(temp_addr.sin_addr),ntohs(temp_addr.sin_port), len, buf);
                                    fflush(stdout);
                                    fwrite(buf, 1, len, fp);
                                    memset(buf, 0, sizeof(buf));                
                                }
                                // 文件打开后,一定要正确关闭!!!!!!
                                fclose(fp);
                                pthread_mutex_unlock(&mut[para->num]);
                                printf("recv ends!\n");
                                close(data_sockfd);                     // 短连接,数据收发完就关闭
                            }
                        } else {
                            printf("code = %d\n", code);
                        }
                    }
                }   //for
                printf("for ends\n");
            }
            close(sockfd);      // 传完断开长连接
            p = p->next;
        }
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
    s_addr.sin_addr.s_addr = htons(INADDR_ANY);
    
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

