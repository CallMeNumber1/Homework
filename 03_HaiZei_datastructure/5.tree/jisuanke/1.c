/*************************************************************************
	> File Name: 1.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月30日 星期二 15时51分11秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Node *build(char pre_str[], char in_str[], int len) {
    Node *root = init(pre_str[0]);
    int pos = strchr(in_str, pre_str[0]) - in_str;
    // 左子树非空
    if (pos > 0) {
        root->lchild = build(pre_str + 1, in_str, pos);
    }
    // 右子树非空
    if (pos < len - 1) {
        root->rchild = build(pre_str + pos + 1, in_str + pos + 1, len - pos - 1);
    }
    return root;
}

void postorder(Node *node) {
    if (node == NULL) return;
    postorder(node->lchild);
    postorder(node->rchild);
    printf("%c", node->data);
}

Node *reverse(Node *root) {
    if (root == NULL) return root;
    Node *temp = root->lchild;
    root->lchild = root->rchild;
    root->rchild = temp;
    reverse(root->lchild);
    reverse(root->rchild);
    return root;
}

void test(Node *root) {
    root = NULL;
    return ;
}
int main() {
    char pre_str[50], in_str[50];
    scanf("%s", pre_str);
    scanf("%s", in_str);
    Node *root = build(pre_str, in_str, strlen(pre_str));    
    postorder(root);
    printf("\n");
    postorder(reverse(root));
    printf("\n");
    return 0;
}

