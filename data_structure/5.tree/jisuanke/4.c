/*************************************************************************
	> File Name: 2.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月30日 星期二 16时42分44秒
 ************************************************************************/
// 此题后掌握的东西
// 由广义表字符串创建二叉链表
// 将二叉链表输出为广义表字符串的形式
// 从二叉树中找具有特定值的节点
// 找节点的父节点
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Stack {
    Node **data;
    int top, size; 
} Stack;

Node *init(char data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}
// 由广义表创建二叉链表
Node *build_tree(const char *str) {
    Node *p = NULL, *root = NULL;
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (Node **)malloc(sizeof(Node *) * 100);
    s->size = 100;s->top = -1;
    int k = 0;
    while (str[0]) {
        switch (str[0]) {
            case '(': {
                s->data[++s->top] = p;
                k = 0;
            } break;
            case ')': {
                s->top--;    
            } break;
            case ',': {
                k = 1;
            }
            case ' ': break;
            default: {
                p = init(str[0]);
                if (root == NULL) root = p;
                if (s->top == -1) break;
                if (k == 0) s->data[s->top]->lchild = p;
                else s->data[s->top]->rchild = p;
            } break;
        }
        str++;
    }
    return root;
}
void inorder(Node *root) {
    if (root == NULL) return ;
    inorder(root->lchild);
    printf("%c ", root->data);
    inorder(root->rchild);
    return ;
}
void level_order(Node *root) {
    Node **data = (Node **)malloc(sizeof(Node *) * 100);
    int head = 0, tail = 0;
    data[tail++] = root;
    while (head < tail) {
        Node *p = data[head];
        printf("%c ", p->data);
        head++;
        if (p->lchild != NULL) {
            data[tail++] = p->lchild;
        }
        if (p->rchild != NULL) {
            data[tail++] = p->rchild;
        }
    }
    return ;
}
int main() {
    char str[100];
    scanf("%[^\n]s", str);
    getchar();
    if (str[0] == '\0') {
        printf("\n");
        return 0;
    }
    Node *root = build_tree(str);
    level_order(root);
    printf("\n");
    return 0;
}

