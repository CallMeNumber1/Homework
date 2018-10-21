/*************************************************************************
	> File Name: 4.stack.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月21日 星期日 19时15分25秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Stack {
    int *data;
    int top, size;
} Stack;

Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->top = -1;
    s->size = n;
    return s;
}

int empty(Stack *s) {
    return s->top == -1;
}

int top(Stack *s) {
    if (empty(s)) return 0;
    return s->data[s->top];
}
int push(Stack *s, int value) {
    if (s->top + 1 == s->size) return 0;
    s->top += 1;
    s->data[s->top] = value;
    return 1;
}

void pop (Stack *s) {
    if (empty(s)) return ;
    s->top -= 1;
    return ;
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

void output(Stack *s) {
    printf("Stack = [");
    for (int i = s->top; i >= 0; --i) {
        printf(" %d", s->data[i]);
        i && printf(",");
    }
    printf("]\n");
    return ;
}
int main() {
    srand(time(0));
    #define MAX_OP 20
    Stack *s = init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4, value = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2:
                printf("push %d to stack\n", value);
                push(s, value);
                output(s);
                break;
            case 3:
                printf("pop %d from stack\n", top(s));
                pop(s);
                output(s);
                break;
                
        }
    }
    
    clear(s);
    return 0;
}
