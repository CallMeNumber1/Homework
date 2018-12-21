/*************************************************************************
	> File Name: 1.vector.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月11日 星期四 18时57分50秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DEFAULT_ARG(a, b) ((#a)[0] ? a + 0 : b)
#define init(a) __init(DEFAULT_ARG(a, 10))

typedef struct Vector {
    int *data;
    int size, length;
}Vector;

Vector *__init(int n) {
    Vector *p = (Vector *)malloc(sizeof(Vector));
    p->data = (int *)malloc(sizeof(int) * n);
    p->size = n;
    p->length = 0;
    return p;
}

void clear(Vector *v) {
    if (v == NULL) return;
    free(v->data);
    free(v);
    return ;
}
// 当内存分配失败时,会返回空地址,为防止内存泄露,要先判断是否成功
int expand(Vector *v) {
    printf("[%p] expanding\n", v->data);
    int *p = (int *)realloc(v->data, sizeof(int) * 2 * v->size);
    if (p == NULL) return 0; 
    v->data = p;
    v->size *= 2;
    printf("[%p] expand vector success, the new size: %d\n", v->data, v->size);
    return 1;
}
// 改进二 动态申请内存
int insert(Vector *v, int value, int ind) {
    if (v->length == v->size) {
        if (expand(v) == 0) {
            return 0;
        }
    }
    if (ind < 0 || ind > v->length) return 0;
    for (int i = v->length - 1; i >= ind; i--) {
        v->data[i + 1] = v->data[i];
    }
    v->data[ind] = value;
    v->length += 1;
    return 1;
}

int erase(Vector *v, int ind) {
    if (v->length == 0) return 0;
    if (ind < 0 || ind >= v->length) return 0;
    for (int i = ind + 1; i < v->length; i++) {
        v->data[i -  1] = v->data[i];
    }
    v->length -= 1;
    return 1;
}
// 相关的结构操作根据需求封装, 方便使用
void output(Vector *v) {
    printf("Vector = [");
    for (int i = 0; i < v->length; i++) {
        printf(" %d", v->data[i]);
    }
    printf("]\n");
    return ;
}
// 改进1:因为每次都是固定大小,考虑改进成不指定大小就有默认值的
// 给c语言加上默认参数
int main() {
    Vector *v = init(10); 
    #define MAX_OP 40
    for (int t = 0; t < MAX_OP; t++) {
        int op = rand() % 4, ind, value;
        switch (op) {
            case 2:
            case 3:
            case 0: {
                // 随机到的值是-1到length+1
                ind = rand() % (v->length + 3) - 1;    
                value = rand() % 100;
                printf("[%d] insert(%d, %d) to vector\n", insert(v, value , ind), value, ind);
                output(v);
            } break;
            case 1: {
                ind = rand() % (v->length + 3) - 1;    
                printf("[%d] erase(%d) from vector\n", erase(v, ind), ind);
                output(v);
            } break;
        }
    }
    // 回收空间
    clear(v); 
    return 0;
}
