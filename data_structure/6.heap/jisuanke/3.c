/*************************************************************************
	> File Name: 3.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月01日 星期四 19时39分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int pi, di;
} Node;

typedef struct Heap {
    Node *data;
    int size;
} Heap;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
    return ;
}
int cmp(Node a, Node b) {
    if (a.pi < b.pi) return 1;
    if (a.pi == b.pi && a.di < b.di) return 1;
    return 0;
}
void push(Heap *h, Node value) {
    h->data[++(h->size)] = value;
    int ind = h->size; 
    while (ind > 1) {
        if (cmp(h->data[ind], h->data[ind / 2])) {
            swap(&h->data[ind], &h->data[ind / 2]);
        }
        ind /= 2;
    }
    return ;
}

void pop(Heap *h) {
    swap(&h->data[h->size], &h->data[1]);
    h->size--;
    int ind = 1;
    while (ind * 2 <= h->size) {
        int max_ind = ind;
        if (cmp(h->data[ind * 2], h->data[max_ind])) {
            max_ind = ind * 2;
        }
        if (ind * 2 + 1 <= h->size && cmp(h->data[ind * 2 + 1], h->data[max_ind])) {
            max_ind = ind * 2 + 1;
        }
        if (max_ind == ind) break;
        swap(&h->data[ind], &h->data[max_ind]);
        ind = max_ind;
    }
    return ;
}

Node top(Heap *h) {
    return h->data[1];
}

void output(Heap *h) {
    for (int i = 1; i <= h->size; i++) {
        printf("%d %d\n", h->data[i].pi, h->data[i].di);
    }
    return ;
}
int main() {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    Node temp;
    int t, n, cnt = 0, ans = 0;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%d", &n);
        h->data = (Node *)malloc(sizeof(Node) * (n + 1));
        h->size = 0;
        for (int j = 1; j <= n; j++) {
            scanf("%d%d", &temp.pi, &temp.di);
            push(h, temp);
        }
        //printf("h->size %d\n", h->size);
        //output(h);
        while (h->size > 0) {
            cnt++;
            Node node = top(h);
            pop(h);
            ans = node.pi;
            if (cnt % 2) {
                node.pi += node.di;
                push(h, node);
            }
            //output(h);
        }
        printf("%d\n", ans);
    }
    return 0;
}


