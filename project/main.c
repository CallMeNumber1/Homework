/*************************************************************************
	> File Name: thread.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月13日 星期二 20时02分50秒
 ************************************************************************/

#include "common.h"
#include "get_conf_value.h"
#include "socket_create.h"
#include "delete_node.h"
#include "insert.h"
#include "find_min.h"
#include "isrepeat.h"
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
    char logfile[20];
    sprintf(logfile, "%d.log", num);
    FILE *log = fopen(logfile, "a+");
    printf("\033[33m-----queue[%d]:%d个元素-----\033[0m", num, queue[num]);
    printf("[ ");
    fprintf(log, "[ ");
    while (p) {
        printf("%s:%d ", inet_ntoa(p->addr.sin_addr), p->addr.sin_port);
        fprintf(log, "%s:%d ", inet_ntoa(p->addr.sin_addr), p->addr.sin_port);
        p = p->next;
    }
    printf("]\n");
    fprintf(log, "]\n");
}
void *func(void *arg);

int main() {
    pthread_mutex_init(&mut, NULL);
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
        pthread_mutex_lock(&mut);
        ret = insert(linkedlist[ind], temp, confd);
        linkedlist[ind] = ret.next;
        queue[ind]++;
        pthread_mutex_unlock(&mut);
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
void *func(void *arg) {
    mypara *para = (mypara *)arg;
    while (1) {
        Node *p = linkedlist[para->num];
        while (p) {
            // 先判断client是否还活着
            int sockfd;
            if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                perror("Socket");
                exit(0);
            }
            // 连接client
            if (connect(sockfd, (struct sockaddr *)&p->addr, sizeof(p->addr)) < 0) {
                perror("connect");
                //printf("sockfd = %d\n", sockfd);
                pthread_mutex_lock(&mut);
                Node ret = delete_node(linkedlist[para->num], para->num, p->addr);
                linkedlist[para->num] = ret.next;
                queue[para->num]--;
                printf("queue[%d]剩余 %d 个元素\n", para->num, queue[para->num]);
                pthread_mutex_unlock(&mut);
                output2(linkedlist[para->num], para->num);
            } else {
                //printf("p->addr: %s:%d\n", inet_ntoa(p->addr.sin_addr), p->addr.sin_port);
                sleep(2);
            }
            p = p->next;
        }
    }
}
