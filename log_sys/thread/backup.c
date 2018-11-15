/*************************************************************************
	> File Name: thread.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月13日 星期二 20时02分50秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
// 最多设置的线程数
#define MAX 10

typedef struct para {
    char *s;
    int num;
} para;

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node insert(Node *head, int val) {
    Node ret;
    ret.next = head;
    Node *p = (Node *)malloc(sizeof(Node));
    p->next = ret.next;
    ret.next = p;
    return ret;
}

void ouput(Node *head) {
    Node *p = head;
    printf("[ ");
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("]\n");
}

void *print_xs(void *arg) {
    while (1) {
        printf("[%d] this is a thread %lu\n", *(int *)(arg), pthread_self());
        sleep(1);    
    }   
}
int main() {
    pthread_t tid[2];
    int i;
    for (i = 0; i < 2; i++) {
        int *temp = (int *)malloc(sizeof(int));
        *temp = i;
        pthread_create(&tid[i], NULL, &print_xs, (void *)temp);
    }
    //　不加此语句时，主线程会先结束，导致整个进程结束
    pthread_join(tid[0], NULL); //等待当前执行的线程完毕
    pthread_join(tid[1], NULL);
    return 0;
}

