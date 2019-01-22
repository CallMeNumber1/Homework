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

void build_automaton(TrieNode *node) {
    TrieNode **queue = (TrieNode **)malloc(sizeof(TrieNode *) * (MAX_SIZE + 5));
    int head = 0, tail = 0;
    queue[tail++] = node;
    while (head < tail) {
        TrieNode *now = queue[head++];
        for (int i = 0; i < SIZE; i++) {
            //if (now->childs[i] == NULL) continue;
            //变成下面的形式 则可以去掉下面的for循环
            if (node->childs[i] == NULL) {
                if (now != node) now->childs[i] = now->fail->childs[i];
                continue;
            }
            TrieNode *p = now->fail;
            // 当指向当前节点的失败指针时，上面都已经并完了
            // 因此可以删去while循环
            p = now->fail->childs[i];
           // while (p &&  p->childs[i] == NULL) p = p->fail;
            if (p == NULL) p = node;
            else p = p->childs[i];
            now->childs[i]->fail = p;
            queue[tail++] = now->childs[i];
        }

        /*
        // AC自动机的线索化
        // 加上个条件：当前节点不能是整个数的根节点
        for (int i = 0; i < SIZE && now != node; i++) {
            if (now->childs[i]) continue;
            now->childs[i] = now->fail->childs[i];
            // 因为时层序遍历
            // 在处理第n层时，第n-1层已经合并完了
        }
        */
    }
    return ;
}

//
void build_automaton_(TrieNode *node) {
    TrieNode **queue = (TrieNode **)malloc(sizeof(TrieNode *) * (MAX_SIZE + 5));
    int head = 0, tail = 0;
    queue[tail++] = node;
    while (head < tail) {
        TrieNode *now = queue[head++];
        for (int i = 0; i < SIZE; i++) {
            if (node->childs[i] == NULL) {
                // 增加了一句话，去掉了一个循环
                
                if (now != node) now->childs[i] = now->fail->childs[i];
                continue;
            }
            TrieNode *p = (now->fail ? now->fail->childs[i] : node);
            if (p == NULL) p = node;
            now->childs[i]->fail = p;
            queue[tail++] = now->childs[i];
        }
    }
    free(queue);
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
