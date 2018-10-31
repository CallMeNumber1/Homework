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
// 将二叉链表输出为广义表的形式
void output(Node *root) {
    if (root == NULL) return ;
    printf("%c", root->data);
    if (root->lchild == NULL && root->rchild == NULL) return ;
    if (root->lchild != NULL || root->rchild != NULL) {
        printf("(");
    }
    if (root->lchild != NULL) {
        output(root->lchild);
    }
    if (root->rchild != NULL) {
        printf(",");
        output(root->rchild);
        printf(")");
    }
    if (root->rchild == NULL) {
        printf(")");
    }
    return;   
}

// 找到值为val的节点
Node *find(Node *root, char val) {
    Node *node = NULL;
    if (root == NULL) return node;
    if (root->data == val) {
        node = root;
        return node;
    }
    Node *p = find(root->lchild, val);
    if (p != NULL) node = p;
    p = find(root->rchild, val);
    if (p != NULL) node = p;
    return node;
}
// 找到值为val节点的父亲节点,用来实现删除
Node *find_parent(Node *root, Node *des) {
    Node *node = NULL;
    if (root == NULL) return node;
    if (root->lchild == NULL && root->rchild == NULL) return node;
    if (root->lchild != NULL) {
        if (root->lchild == des) {
            node = root;
            return node;
        }
    }
    if (root->rchild != NULL) {
        if (root->rchild == des) {
            node = root;
            return node;
        }
    }
    Node *p = find_parent(root->lchild, des);
    if (p != NULL) node = p;
    p = find_parent(root->rchild, des);
    if (p != NULL) node = p;
    return node;
}
int main() {
    char str[100] = {0}, c;
    scanf("%[^\n]s", str);
    getchar();
    scanf("%c", &c);
    if (str[0] == '\0') {
        printf("\n");
        return 0;
    }
    Node *root = build_tree(str);
    Node *p = find(root, c);
   // p == NULL || printf("p->data %c\n", p->data);
    Node *q = find_parent(root, p);
    if (p == NULL) {
        output(root);
        return 0;
    }
    if (q == NULL) {
        printf("\n");
    } else {
        if (q->lchild == p) {
            q->lchild = NULL;
        } else if (q->rchild == p) {
            q->rchild = NULL;
        }
        output(root);
    }
    return 0;
}

