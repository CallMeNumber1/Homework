/*************************************************************************
	> File Name: 1.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月03日 星期六 09时49分48秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 20
#define ERROR 0
#define OK 1

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
	if (s->top >= s->size) return 0;
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

int precede(char a, char b) {
    int pri_a, pri_b;
    if (a == '*' || a == '/') pri_a = 1;
    else pri_a = 0;
    if (b == '*' || b == '/') pri_b = 1;
    else pri_b = 0;
    return pri_a > pri_b;
}
int operate(char theta, int a, int b) {
    if (theta == '*') {
        return a * b;
    } else if (theta == '/') {
        return a / b;
    } else if (theta == '+') {
        return a + b;
    } else if (theta == '-') {
        return a - b;
    }
}
void calc(Stack *numbers, Stack *operators) {
	int a = top(numbers);
    pop(numbers);
    int b = top(numbers);
    pop(numbers);
    push(numbers, operate(top(operators), b, a));
    pop(operators);
    return ;
}

void clear(Stack *s) {
    free(s->data);
    free(s);
    return ;
}

int main() {
    Stack *numbers = (Stack *)malloc(sizeof(Stack));
    init(numbers, MAX);
    Stack *operators = (Stack *)malloc(sizeof(Stack));
    init(operators, MAX);
    char *buffer = (char *)malloc(sizeof(char) * (MAX + 1));
    scanf("%s", buffer);
    int i = 0, m = strlen(buffer);
    while (i < m) {
        if (buffer[i] >= '0' && buffer[i] <= '9') {
            int num = 0;
        	while (buffer[i] >= '0' && buffer[i] <= '9') {
            	num = num * 10 + (int)(buffer[i] - '0');
        		i++;
        	}
            push(numbers, num);
        } else {
            if (empty(operators) || precede(buffer[i], top(operators))) {
            	push(operators, buffer[i]);
                i++;
            } else {
                calc(numbers, operators);
            }
        }
    }
    while (!empty(operators)) {
        calc(numbers, operators);
    }
    printf("%d\n", top(numbers));
    return 0;
}

