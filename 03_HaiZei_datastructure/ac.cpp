/*************************************************************************
	> File Name: ac.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月20日 星期日 10时50分12秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 26;
const char BASE = 'a';
#define MAX_SIZE 100000
typedef struct TrieNode {
    int flag;
    struct TrieNode *next[26], *fail;
} TrieNode, *Trie;

TrieNode* new_node() {
    return (TrieNode *)calloc(1, sizeof(TrieNode));
}

void clear() {
    
}

void insert(TrieNode *trie, char *buffer) {
	TrieNode *p = trie;
    for (int i = 0; i < strlen(buffer); i++) {
        if (p->next[buffer[i] - BASE] == NULL) {
            p->next[buffer[i] - BASE] = new_node();
        }
        p = p->next[buffer[i] - BASE];
    }
    // 为何要+=1？？？
    p->flag += 1;
    return ;
}

void build_automaton(TrieNode *root) {
    TrieNode *q[MAX_SIZE];
	int head = 0, tail = 0;
    root->fail = NULL;
    q[tail++] = root;
    while (head < tail) {
        TrieNode *now = q[head++];
        for (int i = 0; i < SIZE; i++) {
            if (now->next[i] == NULL) continue;
            TrieNode *p = now->fail;
            while (p && p->next[i] == NULL) p = p->fail;
            if (p == NULL) 	now->next[i]->fail = root;
            else now->next[i]->fail = p->next[i];
            q[tail++] = now->next[i];
        }
    }
    return ;
}

int match_count(TrieNode *root, const char *str) {
	int cnt = 0;
    TrieNode *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BASE;
        while (p && p->next[ind] == NULL) p = p->fail;
        if (p == NULL) p = root;
        else p = p->next[ind];
        TrieNode *q = p;
        while (q) {
            cnt += q->flag;
            q = q->fail;
        }
    }
    return cnt;
}

int main() {
    int n;
    char pattern[25];
    char buffer[100005];
    scanf("%d", &n);
    TrieNode *root = new_node();
    for (int i = 0; i < n; i++) {
        scanf("%s", pattern);
        insert(root, pattern);
    }
    build_automaton(root);
    scanf("%s", buffer);
    printf("%d\n", match_count(root, buffer));
    return 0;
}
