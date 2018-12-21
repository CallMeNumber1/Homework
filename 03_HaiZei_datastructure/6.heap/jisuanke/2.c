/*************************************************************************
	> File Name: 2.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月01日 星期四 15时28分00秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 50005
typedef struct Data {
    int f;
    int s;
    int value;
    int ind;
} Data;
typedef struct Heap { 
    Data *data;;
    int size;
} Heap;

void swap(Data *a, Data *b) {
    Data temp = *a;
    *a = *b;
    *b = temp;
    return ;
}

void output(Heap *h) {
    return ;
}
void push(Heap *h, Data d) {
    h->data[++(h->size)] = d;
    int ind = h->size;
    while (ind > 1) {
        if (h->data[ind].value > h->data[ind / 2].value) {
            swap(&h->data[ind], &h->data[ind / 2]);
        }  
        ind /= 2;
    }
    return ;
}
void pop(Heap *h) {
    swap(&h->data[1], &h->data[h->size]);
    h->size--;
    int ind = 1;
    while (ind * 2 <= h->size) {
        int max_ind = ind;
        if (h->data[max_ind].value < h->data[ind * 2].value) {
            max_ind = ind * 2;
        }
        if (ind * 2 + 1 <= h->size && h->data[max_ind].value < h->data[ind * 2 + 1].value) {
            max_ind = ind * 2 + 1;
        }
        // 没有此句时会死循环
        if (max_ind == ind) {
            break;
        } 
        swap(&h->data[max_ind], &h->data[ind]);
        ind = max_ind;
    }
    return ;
}
int top(Heap *h) {
    return (h->data[1].ind);
}

int main() {
    int t, n;
    Data temp;
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->size = 0;
    Heap *h2 = (Heap *)malloc(sizeof(Heap));
    h2->size = 0;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        scanf("%d", &n);
        h->data = (Data *)malloc(sizeof(Data) * (n + 1));
        h->size = 0;
        for (int j = 1; j <= n; j++) {
            scanf("%d%d", &temp.f, &temp.s);
            // 初值为f
            temp.value = temp.f;
            temp.ind = j;
            push(h, temp);
        }
        printf("Case #%d:\n", i);
        h2->data = (Data *)malloc(sizeof(Data) * (n + 1));
        h2->size = 0;
        // 弹出n次
        for (int j = n; j >= 1; j--) {
            printf("%d", top(h));
            pop(h);
            h->size = 0;
            j == 1 || printf(" ");
            for (int k = 1; k <= j - 1; k++) {
                h->data[k].value += h->data[k].s;
                push(h, h->data[k]);
            }
            //h = h2;
        }
        printf("\n");
        //printf("h->size : %d\n", h->size);
    }
    return 0;
}
