/*************************************************************************
	> File Name: 6.twoWay.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月13日 星期六 22时59分00秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;
typedef struct List {
    int length;
    Node head;
} List;

int main() {
    int n, num;
    List *l = (List *)malloc(sizeof(List));
    l->length = 0;
    l->head.next = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        Node *p = (Node *)malloc(sizeof(Node));
        p->data = num;
        p->next = 
    }


    return 0;
}
