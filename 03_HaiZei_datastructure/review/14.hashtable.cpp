/*************************************************************************
	> File Name: 14.hashtable.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月06日 星期日 18时55分09秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *str;
    struct Node *next;      // 使用拉链法(每个节点都是一个链表)
} Node;

typedef struct HashTable {
    // 链表头结点数组
    Node **data;                // 数据区
    int size;                   // 哈希表大小
} HashTable;

// 要存储的字符串
// 使用头插法，因此传入原链表头地址
Node *init_node(char *str, Node *head) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->str = strdup(str);           // 申请一片新空间，并拷贝str内容，返回新存储空间的地址
    p->next = head;
    return p;
}


// 字符串哈希的经典函数
int BKDRHash(char *str) {
    int seed = 31, hash = 0;
    for (int i = 0; str[i]; i++) hash = hash * seed + str[i];
    return hash & 0x7fffffff;   //保证返回一个正值
}


// 将字符串插入哈希表
int insert(HashTable *h, char *str) {
    // 哈希值
    int hash = BKDRHash(str);
    int ind = hash % h->size;   // 哈希值转化为数组下标
    // 1.拉链法的头插法 冲突处理
    h->data[ind] = init_node(str, h->data[ind]);
    /* 2.开放定址法
    int times = 0;                      // 往后试探的次数
    Node *node = init_node(str, NULL);
    while (h->data[ind] != NULL) {      // 当前位置被占用了
        times++;
        ind += times * times;           // 二次试探法
        ind %= h->size;
    }
    h->data[ind] = node;                // 新的位置来存放node
    */
    return 1;
}

// 查找是否有这个字符串
int search(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    Node *p = h->data[ind];
    // 当p不为空并且p指向的str不等于str，往后走
    while (p && strcmp(p->str, str)) p = p->next;
    return p != NULL;
}

HashTable *init_hashtable(int n) {
    // 通常开大一点，两倍即可
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1;
    h->data = (Node **)calloc(sizeof(Node *), h->size);
    return h;
}


void clear_node(Node *node) {
    if (node == NULL) return ;
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
