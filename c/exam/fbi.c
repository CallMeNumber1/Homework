/*************************************************************************
	> File Name: fbi.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月23日 星期五 10时11分21秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

char check(char *str, int len) {
    int num0 = 0, num1 = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '0') num0 = 1;
        if (str[i] == '1') num1 = 1;
    }
    if (num0 && num1) {
        return 'F';
    } else if (num0) {
        return 'B';
    } else if (num1) {
        return 'I';
    }
}
Node *build(char *str, int len) {
    //printf("len = %d\n", len);
    //for (int i = 0; i < len; i++) {
    //    printf("%c", str[i]);
    //}
    //printf("\n");
    if (len <= 0) return NULL;
    Node *root = (Node *)malloc(sizeof(Node));
    root->data = check(str, len);
    root->lchild = build(str, len / 2);
    root->rchild = build(str + (len / 2), len / 2);
    // 在这个位置不能打印输出root->lchild,rchild因为还没返回，即root的子树还没有建立
    return root;
}
void postorder(Node *root) {
    if (root == NULL) return ;
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%c", root->data);
    return ;
}
int main() {
    int n;
    char str[100];
    scanf("%d", &n);
    scanf("%s", str);
    int len = strlen(str);
    Node *head = build(str, len);
    postorder(head);
    printf("\n");
    return 0;
}
