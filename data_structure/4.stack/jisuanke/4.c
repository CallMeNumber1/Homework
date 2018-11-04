/*************************************************************************
	> File Name: 4.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月03日 星期六 23时02分15秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 25

typedef struct Stack {
    int *data;
    int top, size;
} Stack;

void init(Stack *s, int n) {
    s->data= (int *)malloc(sizeof(int) * n);
    s->size = n;
    s->top = -1;
    return ;
}

int empty(Stack *s) {
    return s->top == -1;
}
int push(Stack *s, int val) {
    if (s->top >= s->size) return 0;
    s->data[++(s->top)] = val;
    return 1;
}
int pop(Stack *s) {
    if (empty(s)) return 0;
    s->top--;
    return 1;
}
int top(Stack *s) {
    if (empty(s)) return 0;
    return s->data[s->top];
}
int main() {
    char str[MAX];
    char c;
    int flag = 1;
    Stack *s1 = (Stack *)malloc(sizeof(Stack));
    init(s1, MAX);
    Stack *s2 = (Stack *)malloc(sizeof(Stack));
    init(s2, MAX);
    Stack *temp = (Stack *)malloc(sizeof(Stack));
    init(temp, MAX);
    while (scanf("%c", &c) != EOF) {
        if (c != '@' && c != '\n') push(s1, c), push(temp, c);
    }
    //printf("s1->top: %d\n", s1->top);
    while (!empty(s1)) {
        //printf("top(s1): %c\n", top(s1));
        push(s2, top(s1));
        pop(s1);
    }
    while (!empty(s2)) {
       // printf("top(s2): %c top(temp) %c\n", top(s2), top(temp));
        if (top(temp) != top(s2)) {
            flag = 0;
        }
        pop(s2);
        pop(temp);
    }
    printf("%s\n", flag ? "true" : "false");
    return 0;
}
