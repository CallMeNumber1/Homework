/*************************************************************************
	> File Name: binary_trie.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月23日 星期三 12时57分41秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 2
typedef struct Node {
    int flag;
    struct Node *next[2];
} Node;

Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    for (int i = 0; i < SIZE; i++) {
        p->next[i] = NULL;
    }
    p->flag = 0;
    return p;
}

/*
char *str2binary(char *str) {
    for (int i = 0; str[i]; i++) {
        for (int j = 7; j >= 0; j--) {
            while (i >> 1)
        }
    }  
}
*/
void insert(Node *node, char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        // 得到字符对应的每一个二进制位,并将其插入字典树中
        for (int j = 7; j >= 0; j--) {
            int bit = ((str[i] & (1 << j)) != 0);
            if (p->next[bit] == NULL) p->next[bit] = getNewNode();
            p = p->next[bit];
        }
    }  
    p->flag = 1;
    return ;
}
int search(Node *node, char *str) {
    Node *p = node;
    for (int i = 0; str[i]; i++) {
        for (int j = 7; j >= 0; j--) {
            int bit = ((str[i] & (1 << j)) != 0);
            if (p->next[bit] == NULL) return 0;
            p = p->next[bit];
        }
    }
    return p->flag;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < SIZE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}
int main() {
    Node *root = getNewNode();
    char str[100];
    int op;
    while (scanf("%d%s", &op, str) != EOF) {
        switch (op) {
            case 1: {
                printf("insert %s to trie\n", str);
                insert(root, str);
            } break;
            case 2: {
                printf("search %s from trie = %d\n", str, search(root, str));
            } break;
        }
    }
    clear(root);
    
    return 0;    
}
