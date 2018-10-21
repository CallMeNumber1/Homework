/*************************************************************************
	> File Name: 5.reverse.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月13日 星期六 22时37分36秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
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

Node *new_node(char value) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = value;
    p->next = NULL;
    return p;
}

void output(List *l) {
    Node *p = l->head.next;
    int len = l->length - 1;
    while (len--) {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("%c\n", p->data);
}
int main() {
    int n;
    char c;
    List *l = init();
    scanf("%d", &n);
    // 特判
    if (n == 0) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        getchar();
        scanf("%c", &c);
        Node *p = new_node(c);
        p->next = l->head.next;
        l->head.next = p;
        l->length++;
        //printf("%c %d\n", p->data, l->length);
    }
    output(l);

    return 0;
}

