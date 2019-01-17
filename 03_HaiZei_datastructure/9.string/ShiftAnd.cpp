#include<cstdio>
#include<cstdlib>
#include<iostream>
#define MAXN 10
using namespace std;

typedef struct Bitset {
    int *data;
    int size;
} Bitset;

Bitset *init(int n) {
    Bitset *p = (Bitset *)malloc(sizeof(Bitset));
    p->data = (int *)malloc(sizeof(int) * n);
    p->size = n;
    return p;
}

int expand(Bitset *bit, int n) {//扩充n的空间
    int *p = (int *)realloc(bit->data, sizeof(int) * (n + bit->size) + 1);//报realloc的错，改成加１就好了？？？
    //printf("扩充后的空间为%d\n", n + bit->size);
    if (p == NULL) return 0;
    bit->data = p;
    bit->size += n;
    return 1;
}

Bitset *Shift(Bitset *a, int n) {
    expand(a, n);
    int len1 = a->size;
    for (int i = len1 - 1; i >= 0; i--) {
        a->data[i + n] = a->data[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        a->data[i] = 0;
    }
    return a;
}

Bitset *And(Bitset *a, Bitset *b) {
    if (a->size < b->size) {
        expand(a, b->size - a->size);
    } else if (a->size > b->size) {
        expand(b, a->size - b->size);
    }
    int len = a->size;
    for (int i = 0; i < len; i++) {
        a->data[i] = a->data[i] & b->data[i];
    }
    return a;
}

Bitset *Or(Bitset *a, Bitset *b) {
    if (a->size < b->size) {
        expand(a, b->size - a->size);
    } else if (a->size > b->size) {
        expand(b, a->size - b->size);
    }
    int len = a->size;
    for (int i = 0; i < len; i++) {
        a->data[i] = a->data[i] | b->data[i];
    }
    return a;
}

void output(Bitset *bit) {
    for (int i = bit->size; i >= 0; i--) {
        printf("%d",bit->data[i]);
    }
    printf("\n");
}

int ShiftAnd(char *str, char *pattern) {
    #define BASE 128
    Bitset *code[BASE];
    int len = 0;
    for (int i = 0; i < BASE; i++) {
        code[i] = init(MAXN);
    }
    for (len = 0; pattern[len]; len++) {
        code[pattern[len]]->data[len] = 1;
    }
    Bitset *p = init(MAXN);
    Bitset *num2 = init(MAXN);
    num2->data[0] = 1;
    for (int i = 0; str[i]; i++) {
        output(p);
        p = And(Or(Shift(p, 1), num2), code[str[i]]);
        if (p->data[len - 1] == 1) {
            return i - len + 1;
        }
    }
    return -1;
    #undef BASE
}

int main() {
    char str[2 * MAXN], pattern[MAXN + 5];
    while (scanf("%s%s", str, pattern) != EOF) {
        printf("模式串位置在%d\n", ShiftAnd(str, pattern));
    }
}