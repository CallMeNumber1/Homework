/*************************************************************************
	> File Name: 3.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月15日 星期二 10时25分47秒
 ************************************************************************/

// 字符串统计
// AC自动机

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 26
#define BEGIN_LETTER 'a'
typedef struct Node {
    int flag, count;
    struct Node *next[BASE], *fail;
    char *str;
} Node;

typedef struct Queue {
    // 存储地址的数据区
    Node **data;
    int head, tail, size;
} Queue;

Queue *init_queue(int n) {
    Queue *q = (Queue *)calloc(sizeof(Queue), 1);
    // 指针数组
    q->data = (Node **)malloc(sizeof(Node *) * n);
    
    q->tail = q->head = 0;
    
    return q;
}
Node *front(Queue *q) {
    return q->data[q->head];
}
void push(Queue *q, Node *node) {
    q->data[q->tail++] = node;
    return ;
}

int empty(Queue *q) {
    return q->head == q->tail;
}

void pop(Queue *q) {
    if (empty(q)) return ;
    q->head++;
}

void clear_queue(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

Node *getNewNode() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}

// 字典树插入
int *insert(Node *root, const char *str) {
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = str[i] - BEGIN_LETTER;
        if (p->next[ind] == NULL) p->next[ind] = getNewNode();
        p = p->next[ind];
    }
    p->flag = 1;
    p->count = 0;
    p->str = strdup(str);
    return &p->count;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

void build_ac(Node *root) {
    Queue *q = init_queue(100005);
    // 第一层失败指针
    root->fail = NULL;
    push(q, root);
    while (!empty(q)) {
        Node *now_node = front(q);
        pop(q);
        // 建立所有子节点失败指针
        for (int i = 0; i < BASE; i++) {
            if (now_node->next[i] == NULL) continue;
            Node *p = now_node->fail;
            // 当非空且没有第i个子孩子
            while (p && p->next[i] == NULL) p = p->fail;
            if (p == NULL) now_node->next[i]->fail = root;
            else now_node->next[i]->fail = p->next[i];
            push(q, now_node->next[i]);
        }
    }
    return ;
}
void match(Node *root, const char *str) {
    int cnt = 0;
    // 需要一个状态跳来跳去
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        // 向哪里跳
        int ind = str[i] - BEGIN_LETTER;
        while (p && p->next[ind] == NULL) p = p->fail;
        if (p == NULL) p = root;
        else  p = p->next[ind];
        // 顺着链走，链上有一个flag为1的则说明找到一个单词
        Node *q = p;
        while (q) {
            if (q->str != NULL) {
                q->count++;
            }
            q = q->fail;
        }
    }
    return ;
}
int main() {
    Node *root = getNewNode();
    // cnt 记录字典树有多少个节点 用来确定队列大小
    int n;
    char str[100005];
    char pattern[1005][25];
    int *ans[1005];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", pattern[i]);
        ans[i] =  insert(root, pattern[i]);
    }
    // build ac
    build_ac(root);

    // 读入文本串
    scanf("%s", str);
    // match ac
    match(root, str);
	for (int i = 0; i < n; i++) {
        printf("%d: %d\n", i, *ans[i]);
    }
    return 0;
}

