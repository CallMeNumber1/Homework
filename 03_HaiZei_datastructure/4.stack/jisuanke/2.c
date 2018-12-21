/*************************************************************************
	> File Name: 2.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月03日 星期六 11时19分55秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 105

typedef struct Stack {
        int *data;
        int top, size;
} Stack;

void init(Stack *s, int size) {
        s->data = (int *)malloc(sizeof(int) * size);
        s->size = size;
        s->top = -1;
        return ;
}

int push(Stack *s, int value) {
        if (s->top >= s->size) {
            printf("push error!\n");
            return 0;
        }
        s->data[++(s->top)] = value;
        return 1;

}

int pop(Stack *s) {
        if (s->top == -1) return 0;
        s->top--;
        return 1;

}

int top(Stack *s) {
        if (s->top == -1) return 0;
        return s->data[s->top];
}

int empty(Stack *s) {
        return s->top == -1;
}


int main() {
    int n, m;
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    scanf("%d", &n);
    // 注意,先输入n才能使用n,否则会出现莫名其妙的错误!!低级错误!!!
    init(stack, n);
    int ind = 0, flag = 1;
    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        while (ind < m) {
            ind++;
            push(stack, ind);
        }
        if (top(stack) != m) {
            flag = 0;
        }
        pop(stack);
    }
    if (flag) printf("YES\n");
    else printf("NO\n");
    return 0;
}

