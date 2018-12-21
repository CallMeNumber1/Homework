/*************************************************************************
	> File Name: 1.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月01日 星期四 14时46分28秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Heap {
    double *data;
    int size;
} Heap;

double calc(double a, double b) {
    return pow(a * pow(b, 2), 1.0 / 3);
}

void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
    return ;
}

void output(Heap *h) {
    for (int i = 1; i <= h->size; i++) {
        printf("%lf ", h->data[i]);
    }
    printf("\n");
}
void push(Heap *h, double value) {
    h->data[++(h->size)] = value;
    int ind = h->size;
    while (ind > 1) {
        if (h->data[ind] > h->data[ind / 2]) {
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
        if (h->data[max_ind] < h->data[ind * 2]) {
            max_ind = ind * 2;
        }
        if (ind * 2 + 1 <= h->size && h->data[max_ind] < h->data[ind * 2 + 1]) {
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
double top(Heap *h) {
    return (h->data[1]);
}
int main() {
    int n, temp, ans;
    scanf("%d", &n);
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->data = (double *)malloc(sizeof(double) * (n + 1));
    h->size = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &temp);
        push(h, temp);
    }
    //output(h);
    // 合并n-1次
    for (int i = 1; i < n; i++) {
        double a = top(h);
        pop(h);
        double b = top(h);
        pop(h);
        push(h, calc(a, b));
    }
    output(h);
    
    return 0;
}

