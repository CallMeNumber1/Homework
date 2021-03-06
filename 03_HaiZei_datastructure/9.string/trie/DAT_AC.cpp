/*************************************************************************
	> File Name: Double_Array_Trie.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月06日 星期日 15时15分22秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 26
// 确定base值，和有多少个子节点有关系
typedef struct Node {
    int flag;
    struct Node *next[SIZE];
} Node;

typedef struct DATNode {
    int base;
    int check;
    int fail;
} DATNode;


Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    p->flag = 0;
    return p;
}

int insert(Node *node, const char *str) {
    Node *p = node;
    int cnt = 0;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - 'a'] == NULL) {
            p->next[str[i] - 'a'] = getNewNode();
            cnt += 1;
        }
        p = p->next[str[i] - 'a'];
    }
    p->flag = 1;
    return cnt;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < SIZE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

int getBase(Node *node, DATNode *trie) {
    int base = 0, flag = 0;     // 合法
    while (!flag) {
        flag  = 1;
        base += 1;
        for (int i = 0; i < SIZE; i++) {
            if (node->next[i] == NULL) continue;
            // 这个位置空着
            if (trie[base + i].check == 0) continue;
            flag = 0;
            break;
        }
    }
    return base;
}

// max 节点坐标
int Transform(Node *node, DATNode *trie, int ind) {
    if (ind == 1) trie[ind].check = 1;
    // 取反
    if (node->flag) trie[ind].check = -trie[ind].check;
    trie[ind].base = getBase(node, trie);
    for (int i = 0; i < SIZE; i++) {
        // 当前节点没有第i孩子
        if (node->next[i] == NULL) continue;
        trie[trie[ind].base + i].check = ind;
    }
    int ret = ind;
    for (int i = 0; i < SIZE; i++) {
        if (node->next[i] == NULL) continue;
        int temp = Transform(node->next[i], trie, trie[ind].base + i);
        if (temp > ret) ret = temp;
    }
    return ret;
}


int search(DATNode *trie, const char *str) {
    int p = 1;  // 根节点
    for (int i = 0; str[i]; i++) {
        int delta = str[i] - 'a';
        int check = abs(trie[trie[p].base + delta].check);
        if (check - p) return 0;
        p = trie[p].base + delta;
    }
    return trie[p].check < 0;
}
// 当前节点是否有子孩子
int has_child(DATNode *trie, int p, int i) {
    return abs(trie[trie[p].base + i].check) == p;
}

// 传入节点数量
void build_ac(DATNode *trie, int cnt) {
    int *queue = (int *)malloc(sizeof(int) * (cnt + 5));
    int head = 0, tail = 0;
    trie[1].fail = 0;
    queue[tail++] = 1;
    while (head < tail) {
        int now = queue[head++];
        for (int i = 0; i < SIZE; i++) {
            if (!has_child(trie, now, i)) continue; 
            int p = trie[now].fail;
            while (p && !has_child(trie, p, i)) p = trie[p].fail;
            if (p == 0) p = 1;
            else p = trie[p].base + i;
            trie[trie[now].base + i].fail = p;
            // 当前节点第i个子孩子压栈
            queue[tail++] = trie[now].base + i;
        }
    }
    return ;
}

int match_count(DATNode *trie, const char *str) {
    int ret = 0;
    int p = 1, q;
    while (str[0]) {
        // p没有走到空节点且p没有此子孩子
        while (p && !has_child(trie, p, str[0]- 'a')) p = trie[p].fail;
        q = p;
        while (q) ret += (trie[q].check < 0), q = trie[q].fail;
        if (p == 0) p = 1;
        str++;
    }
    return ret;
}

int main() {
    int n, cnt1 = 1, cnt2 = 0;
    char str[100];
    Node *root = getNewNode();
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        cnt1 += insert(root, str);
    }
    DATNode *trie = (DATNode *)calloc(sizeof(DATNode), cnt1 * 10);
    cnt2 = Transform(root, trie, 1);   // 当前root的节点编号
    build_ac(trie, cnt2);
    return 0;
}
