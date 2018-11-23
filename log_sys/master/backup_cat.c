/*************************************************************************
	> File Name: thread.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月13日 星期二 20时02分50秒
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
#define PORT 8000
typedef struct mypara {
    char *s;
    //　传入参数标志是哪个线程
    int num;
} mypara;

typedef struct Node {
    struct sockaddr_in addr;
    struct Node *next;
} Node, *LinkedList;

int queue[INS + 1] = {0};
LinkedList linkedlist[INS + 1];

Node insert(Node *head, struct sockaddr_in t_addr) {
    Node ret;
    ret.next = head;
    Node *p = (Node *)malloc(sizeof(Node));
    p->addr = t_addr;
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
int socket_create(int port);
char *get_conf_value(char *path_name, char *key_name, char *value);
int main() {
    // 初始化链表数组
    for (int i = 0; i <= INS; i++) {
        linkedlist[i] = NULL;
    }
    //freopen("in.in", "r", stdin);
    pthread_t t[INS + 1];
    mypara para[INS + 1];
    /*
    for (int i = 0; i < INS; i++) {
        // 设置num的值后将para传入任务，可用来标识线程
        para[i].num = i; 
        para[i].s = "Hello HaiZei!";
        pthread_create(&t[i], NULL, func, (void *)&para[i]);
        printf("Current pthread id = %ld \n", t[i]);
    }
    //　先让子进程执行完毕
    pthread_join(t[0], NULL); //等待当前执行的线程完毕
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);
    pthread_join(t[4], NULL);
    */
   // char str[20];

    // 从配置文件中读取初始化信息
    char value[20];
    char *prename = get_conf_value("./init.conf", "prename", value);
    char *start = get_conf_value("./init.conf", "start", value);
    char *finish = get_conf_value("./init.conf", "finish", value);
    for (int i = atoi(start); i <= atoi(finish); i++) {
        char temp[20];
        strcpy(temp, prename);
        // 不减1,则拼接时会有换行
        sprintf(temp + strlen(temp) - 1, ".%d", i);
        // 封装sockaddr_in结构体
        struct sockaddr_in t_addr;
        t_addr.sin_family = AF_INET;
        t_addr.sin_port = htons(PORT);
        t_addr.sin_addr.s_addr = inet_addr(temp);
        // 选择元素较少的链表插入,均衡线程间的负载
        int ind = find_min(INS, queue);
        Node ret;
        ret = insert(linkedlist[ind], t_addr);
        linkedlist[ind] = ret.next;
        queue[ind]++;

        printf("%s\n", temp);
    }

    /*while (scanf("%s", str) != EOF) {
        printf("%s\n", str);
        // 平衡请求
        // 选择元素做少的链表插入，均衡线程间的负载
        struct sockaddr_in t_addr;
        t_addr.sin_family = AF_INET;
        t_addr.sin_port = htons(PORT);
        t_addr.sin_addr.s_addr = inet_addr(str);
        int ind = find_min(INS, queue);
        Node ret;
        ret = insert(linkedlist[ind], t_addr);
        linkedlist[ind] = ret.next;
        queue[ind]++;

    } */

    for (int i = 0; i < INS; i++) {
        printf("%d ", queue[i]);
        printf(" ....... ");
        output(linkedlist[i]);
    }

    return 0;
}
/*
void *func(void *arg) {
    mypara *para;
    para = (mypara *)arg;
    Node ret;
    // 模拟连接分布不均，来显示后来线程处理时平衡的功能
    for (int i = para->num; i <= 10; i++) {
        ret = insert(linkedlist[para->num], i);
        queue[para->num]++;
        linkedlist[para->num] = ret.next;   
    }
    output(linkedlist[para->num]);
    return NULL;
}
*/
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
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = htons(INADDR_ANY);
    
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