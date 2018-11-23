/*************************************************************************
	> File Name: union2.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月04日 星期四 12时08分06秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Number {
    int type;   //0->int 1->float
    union {
        int num1;
        float num2;
    }N;
};
void print(Number *n) {
    int opt = n->type;
    switch (opt) {
        case 0: {
            printf("%d\n", n->N.num1);
        } break;
        case 1: {
            printf("%f\n", n->N.num2);
        } break;
    }
}
void set(Number *n, int num) {
    n->type = 0;
    n->N.num1 = num;
}
void set(Number *n, float num) {
    n->type = 1;
    n->N.num2 = num;
}
int main() {
    srand(time(0));     //随机种子
    #define MAX_N 2018
    Number arr[MAX_N];
    for (int i = 0; i < MAX_N; i++) {
        int op = rand() % 2;
        switch (op) {
            case 0: {
                int value = rand() % 100;
                set(arr + i, value);
            } break;
            case 1: {
                float value = (1.0 * (rand() % 10000) / 10000) * 100;
                set(arr + i, value);
            } break;
        }
    }
    for (int i = 0; i < MAX_N; i++) {
        print(arr + i);
    }
    arr[0].N.num2 = 1.0;
    printf("arr[0].N.num1 = %d\n", arr[0].N.num1);
    return 0;
}
