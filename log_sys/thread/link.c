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
#define INS 15

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


int find_min(int n, int *arr) {
    int min = 100;
    for (int i = 0; i < n; i++) {
        if (arr[i] < min) min = arr[i]; 
    }
    return min;
}
void *func(void *arg);
int main() {
    LinkedList l = NULL;
    Node ret;
    ret = insert(l, 1);
    l = ret.next;
    ret = insert(l, 2);
    l = ret.next;
    output(l);
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
