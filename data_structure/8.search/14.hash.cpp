/*************************************************************************
	> File Name: 14.hash.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月06日 星期二 20时41分51秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 拉链法,每个位置存储一个节点
typedef struct Node {
    char *str;
    struct Node *next;
} Node;

typedef struct HashTable {
    // 链表头地址数组
    Node **data;  
    int size;
} HashTable;

// 头插法
Node *init_node(char *str, Node *head) {
    Node *p = (Node *)malloc(sizeof(Node));
    // 将str拷贝到新存储空间
    p->str = strdup(str);
    p->next = head;
    return p;
}

// 存储n个元素的哈希表
// 通常开大两倍
HashTable *init_hashtable(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1;
    h->data = (Node **)calloc(sizeof(Node *), h->size);
    return h;
}
// 字符串哈希经典函数
int BKDRHash(char *str) {
    // 为什么要设置成为31
    int seed = 31, hash = 0;
    for (int i = 0; str[i]; i++) hash = hash * seed + str[i];
    // 保证返回正值
    return hash & 0x7fffffff;
}

int insert(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    // 拉链法的头插法
    // 这种冲突处理比较简单
    h->data[ind] = init_node(str, h->data[ind]);
    return 1;
    /*
    // 开放定址法
    // 去找到个新的位置
    int times = 0;
    Node *node = init_node(str, NULL);
    // 被占用时
    while (h->data[ind]) {
        // 二次试探法
        times++;
        ind += times * times;
        ind %= h->size;
    }
    h->data[ind] = node;
    */
}

int search(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    Node *p = h->data[ind];
    while (p && strcmp(p->str, str)) p = p->next;
    return p != NULL;
}
void clear_node(Node *node) {
    if (node == NULL) return ;
    //p当前 q下一个
    Node *p = node, *q;
    while (p) {
        q = p->next;        
        free(p->str);
        free(p);
        p = q;
    }
    return ;
}

void clear_hashtable(HashTable *h) {
    if (h == NULL) return ;
    for (int i = 0; i < h->size; i++) clear_node(h->data[i]);
    free(h->data);
    free(h);
    return ;
}

// 拉链法和BKDRHash实现哈希表
int main() {
    int op;
    char str[100];
    HashTable *h = init_hashtable(100);
    while (scanf("%d%s", &op, str) != EOF) {
        switch (op) {
            case 0: {
                printf("insert %s to HashTable\n", str);
                insert(h, str);
            } break;
            case 1: {
                printf("search %s result = %d\n", str, search(h, str));   
            } break;
        }
    }
    

    return 0;
}
