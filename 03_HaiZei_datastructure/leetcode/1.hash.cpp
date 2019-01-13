/*************************************************************************
	> File Name: 1.hash.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月13日 星期日 15时35分32秒
 ************************************************************************/


// 哈希表做法

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

typedef struct Data {
    int val, pos;
} Data;


typedef struct HashTable {
    Data *data;
    char *flag;
    int n;
} HashTable;

HashTable *init(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->n = n;
    h->data = (Data *)malloc(sizeof(Data) * n);
    h->flag = (char *)calloc(sizeof(char), n);
    return h;
}

int hash_func(HashTable *h, int val) {
    return val % h->n;
}

void insert(HashTable *h, int val, int ind) {
    int hash = hash_func(h, val);
    int time = 1;
    while (h->flag[hash]) {
        hash += (time++);
        hash %= h->n;
    }
    h->data[hash].val = val;
    h->data[hash].pos = ind;
    h->flag[hash] = 1;
    return ;
}

int query(HashTable *h, int val) {
    int hash = hash_func(h, val);
    int time = 1;
    while (h->flag[hash] && h->data[hash].val != val) {
        hash += (time++);
        hash %= h->n;
    }
    if (h->flag[hash] == 0) return -1;
    return h->data[hash].pos;
}

void clear(HashTable *h) {
    if (h == NULL) return ;
    free(h->data);
    free(h);
    return ;
}

#define MAX_N 500
int arr[MAX_N + 5] = {0};

int main() {
    int n, target;
    scanf("%d", &n);
    HashTable *h = init(3 * n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", arr + i);
    }
    scanf("%d", &target);
    for (int i = 1; i <= n; i++) {
        int pos;
        if ((pos = query(h, target - arr[i])) == -1) {
            insert(h, arr[i], i);
            continue;
        }
        printf("%d %d\n", pos, i);
        break;
    }

    clear(h);

    return 0;
}

