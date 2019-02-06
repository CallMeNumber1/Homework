/*************************************************************************
	> File Name: ac_thread.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年02月06日 星期三 13时44分00秒
 ************************************************************************/
/*  AC自动机线索化
	测试用题：计算客:AC自动机的复习一节
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 26;
const char BASE = 'a';
const int MAX_SIZE = 200000;
const int MAX_LEN = 200000;
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
    p->flag++;
    return ;
}

// AC自动机线索化 
void build_automaton(TrieNode *root) {
    TrieNode **queue = (TrieNode **)malloc(sizeof(TrieNode *) * (MAX_SIZE + 5));
    int head = 0, tail = 0;
    queue[tail++] = root;
    while (head < tail) {
        TrieNode *now = queue[head++];
        for (int i = 0; i < SIZE; i++) {
            //变成下面的形式 则可以去掉下面的for循环
            if (now->next[i] == NULL) {
                if (now != root) now->next[i] = now->fail->next[i];
                continue;
            }
            TrieNode *p = (now->fail ? now->fail->next[i] : root);
            // 因为是层序遍历
            // 当指向当前节点的失败指针时，上面都已经并完了
            // 因此可以删去while循环
            if (p == NULL) p = root;
            now->next[i]->fail = p;
            queue[tail++] = now->next[i];
        }
    }
    free(queue);
    return ;
}

int match_count(TrieNode *root, const char *str) {
	int cnt = 0;
    TrieNode *p = root;
    for (int i = 0; str[i]; i++) {
        // 线索化后一步跳转即可
        p = p->next[str[i] - 'a'];
  		TrieNode *q = p;
        while (q) {
            cnt += q->flag;
            q = q->fail;
        }
        if (p == NULL) p = root;
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
