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

Node *build(Node *root, int k, char str[], int dep) {
    printf("%d\n", strlen(str));
    if (2 * k > strlen(str)) return root;
    printf("k = %d\n", k);
    root->lchild = init(str[2 * k]);
    root->rchild = init(str[2 * k + 1]);
    build(root->lchild, k + 1, str, dep);
    build(root->rchild, k + 1, str, dep);
    return root;
}

void preorder(Node *root) {
    if (root == NULL) return ;
    printf("%c ", root->data);
    preorder(root->lchild);
    preorder(root->rchild);
    return ;
}
int main() {
    char data;
    char str[MAX] = {'.'};
    int k = 1;
    while (scanf("%c", &data) != EOF) {
        if (data == ' ') continue;
        if (data == '$') break;
        str[k++] = data;
    }
    str[k] = '\0';
    Node *root = init(str[1]);
    int dep = ceil(log2(k + 1));
    Node *node = build(root, 1, str, dep);
    preorder(node);
    printf("\n");
    return 0;
}
