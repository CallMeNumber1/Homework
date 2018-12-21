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
#define INS 5

typedef struct mypara {
    char *s;
    int num;
} mypara;

typedef struct Node {
    int data;
    struct Node *next;
} Node, *LinkedList;

int queue[INS + 1] = {0};
LinkedList linkedlist[INS + 1];

Node insert(Node *head, int val) {
    Node ret;
    ret.next = head;
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->next = ret.next;
    ret.next = p;
    return ret;
}

void output(Node *head) {
    Node *p = head;
    printf("[ ");
    while (p) {
        printf("%d ", p->data);
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
int main() {
    // 初始化链表数组
    for (int i = 0; i <= INS; i++) {
        linkedlist[i] = NULL;
    }
    freopen("in.in", "r", stdin);
    pthread_t t[INS + 1];
    mypara para[INS + 1];
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
    int temp;
    while (scanf("%d", &temp) != EOF) {
        // 平衡请求
        // 选择元素做少的链表插入，均衡线程间的负载
        int ind = find_min(INS, queue);
        Node ret;
        ret = insert(linkedlist[ind], temp);
        linkedlist[ind] = ret.next;
        queue[ind]++;
    }

    for (int i = 0; i < INS; i++) {
        printf("%d ", queue[i]);
        printf(" ....... ");
        output(linkedlist[i]);
    }
    printf("\n");
    return 0;
}

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
