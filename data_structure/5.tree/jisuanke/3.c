/*************************************************************************
	> File Name: 3.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月30日 星期二 17时57分33秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100
typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

Node *init(char data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}
// 顺序表存储的完全二叉树转为二叉链表存储
Node *build(Node *root, int k, char str[], int len) {
    if (2 * k > len) return root;
    root->lchild = init(str[2 * k]);
    if (2 * k + 1 > len) return root;
    root->rchild = init(str[2 * k + 1]);
    build(root->lchild, 2 * k, str, len);
    build(root->rchild, 2 * k + 1, str, len);
    return root;
}

void preorder(Node *root) {
    if (root == NULL) return ;
    printf("%c ", root->data);
    preorder(root->lchild);
    preorder(root->rchild);
    return ;
}

void general_output(Node *root) {
    if (root == NULL) return;
    printf("%c", root->data);
    if (root->lchild != NULL && root->rchild != NULL) {
        printf("(");
        general_output(root->lchild);
        printf(",");
        general_output(root->rchild);
        printf(")");
    } else if (root->lchild != NULL) {
        printf("(");
        general_output(root->lchild);
        printf(")");
    }
    return ;
}
int main() {
    char data;
    // 不赋初值时,则str长度为0,因为第一位为\0
    char str[MAX] = {'.'};
    int k = 1;
    while (scanf("%c", &data) != EOF) {
        if (data == ' ') continue;
        if (data == '$') break;
        str[k++] = data;
    }
    if (k == 1) return 0;
    str[k] = '\0';
    //printf("%s\n", str);
    int len = strlen(str) - 1;
    //printf("len = %d\n", len);
    Node *root = init(str[1]);
    Node *node = build(root, 1, str, len);
    // 测试二叉树是否建立成功
    //preorder(node);
    //printf("\n");
    general_output(node);
    printf("\n");
    return 0;
}


