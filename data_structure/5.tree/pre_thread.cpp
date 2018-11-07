/*************************************************************************
	> File Name: thread.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月04日 星期日 11时22分48秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define NORMAL 0
#define THREAD 1
typedef struct Node {
    int key, ltag, rtag;
    struct Node *lchild, *rchild;
} Node;

Node *init(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    p->ltag = p->rtag = NORMAL;
    return p;
}

Node *insert(Node *root, int key) {
    if (root == NULL) return init(key);
    if (root->key == key) return root;
    if (key < root->key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}
void preorder(Node *root) {
    if (root == NULL) return ;
    printf("%d ", root->key);
    preorder(root->lchild);
    preorder(root->rchild);
    return ;
}
void build(Node *root) {
    // 当仅用root为空判断空时,有线索也会判定为非空,则递归不会结束
    if (root == NULL || root->ltag == THREAD || root->rtag == THREAD)  return ;
    static Node *pre = NULL;
    // DEBUG
    //printf("%d ", root->key);
    // DEBUG
    // 建立前驱
    if (root->lchild == NULL) {
        root->lchild = pre;
        root->ltag = THREAD;
    }
    //建立后继 
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = root;
        pre->rtag = THREAD;
    }
    pre = root;
    build(root->lchild);
    build(root->rchild);
    return ;
}

// 状态机 四种状态
// 线索化 可实现前序列非递归遍历
// 输出当前节点,如果左子树不空(非线索),则往左走
// 否则,当左子树为空(即记录了后继时),往右走
void output(Node *root) {
    int status = 1;
    Node *p = root;
    while (p) {
        switch(status) {
            case 1: {
                printf("%d ", p->key);
                if (p->ltag == NORMAL) {
                    p = p->lchild;
                    status = 1;
                } else {
                    p = p->rchild;
                }
            } break;
        }
    }
    printf("\n");
    return ;
}
int clear(Node *root) {
    if (root == NULL) return 0;
    root->ltag == NORMAL && clear(root->lchild);
    root->rtag == NORMAL && clear(root->rchild);
    free(root);
    return 0;
}

int output_thread(Node *root) {
    if (root == NULL) return 0;
    printf("key : %d ", root->key);
    if (root->lchild) {
        printf("(ltag: %d, lchild: %d)", root->ltag, root->lchild->key);
    }
    if (root->rchild) {
        printf("(rtag: %d, rchild: %d)", root->rtag, root->rchild->key);
    }
    printf("\n");
    root->ltag == NORMAL && output_thread(root->lchild);
    root->rtag == NORMAL && output_thread(root->rchild);
    return 0;
}
int main() {
    int n;
    Node *root = NULL;
    while (scanf("%d", &n) != EOF) {
        root = insert(root, n);
    }
    preorder(root);
    printf("\n");
    build(root);
    //output_thread(root);
    output(root);
    clear(root);
    return 0;
}
