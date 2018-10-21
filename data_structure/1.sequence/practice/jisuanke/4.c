/*************************************************************************
	> File Name: 4.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月13日 星期六 16时13分45秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 1005

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node head;
    int length;
} List;

List *init() {
    List *l = (List *)malloc(sizeof(List));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

Node *newNode(int value) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = value;
    p->next = NULL;
    return p;
}

void insert(List *l, int value, int ind) {
    Node *p = &(l->head);
    while (ind--) {
        p = p->next;
        if (p == NULL) return ;
    }
    Node *node = newNode(value);
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return ;
}

void erase(List *l, int ind) {
    Node *p = &(l->head);
    while (ind--) {
        p = p->next;
        if (p == NULL) return;
    }
    Node *q = p->next;
    p->next = p->next->next;
    free(q);
    l->length -= 1;
    return ;
}
int main() {
    int n, m, num;
    scanf("%d%d", &n, &m);
    List *list = init();
    for (int i = 0; i < n; i++) {
        insert(list, i + 1, i);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &num);
        erase(list, num - 1);
    }
    int ans = (n - m) / 2;
    Node *p = &(list->head);
    while (ans--) {
        p = p->next;
        if (p == NULL) return 0;
    }
    printf("%d\n", p->next->data);
    return 0;
}

