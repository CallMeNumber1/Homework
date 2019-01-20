/*************************************************************************
	> File Name: ac_dfs.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月20日 星期日 09时46分02秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define BASE 26
#define BEGIN_LETTER 'a'

typedef struct Node {
    int flag;
    struct Node *next[BASE];
    struct Node *fail, *father;
} Node;

Node *getNewNode(Node *father) {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->father = father;
    return p;
}
void insert(Node *root, const char *str) {
    Node *p = root;
    for (int i = 0; i < BASE; i++)  {
        if (p->next[str[i] - BEGIN_LETTER] == NULL) {
            p->next[str[i] - BEGIN_LETTER] = getNewNode(p);
        }
        p = p->next[str[i] - BEGIN_LETTER];
    }
    p->flag = 1;
    return ;
}

// 海贼独家，主要学习递归程序的设计思路
// 递归确定每一个节点失败指针
// 访问所有节点的程序
void build_ac(Node *node) {
    // 因为p可能为根节点，则p->father可能为空，因此要判断一下
    if (node == NULL) return ;
    // 当node为根节点时
    if (node->fail == NULL) build_ac(node->father);
    for (int i = 0; i < BASE; i++) {
        // 在这里确定失败指针
        // 因为正常情况下 往下走之前root当前的失败指针应该已经建立
        if (node->next[i] == NULL) continue;
        // 已经确定过的失败指针不必再确定了
        if (node->next[i]->fail) continue;
        Node *p = node->fail, *pre_p = node;
        // 顺着失败指针找上去
        while (p && p->next[i] == NULL) {
            if (p->fail == NULL) build_ac(p->father);
            pre_p = p;
            p = p->fail;
        }
        // 不必传入一个根节点，会造成浪费
        // 当p为空时，pre_p即为根节点
        if (p == NULL) p = pre_p;
        else p = p->next[i];
        node->next[i]->fail = p;
        build_ac(node->next[i]);
    }
    return ;

}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

int main() {
    Node *root = getNewNode(NULL);
    return 0;
}
