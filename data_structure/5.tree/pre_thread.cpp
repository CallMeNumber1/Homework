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

void build(Node *root) {
    if (root == NULL) return ;
    // 静态变量pre
    static Node *pre = NULL;
    build(root->lchild);
    // 建立前驱索引
    if (root->lchild == NULL) {
        root->lchild = pre;
        // 代表左子树是个线索
        root->ltag = THREAD;
    }
    // 当前节点前驱的后继
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = root;
        pre->rtag = THREAD;
    }
    pre = root;
    build(root->rchild);
    return ;
}

// 状态机 四种状态
void output(Node *root) {
    int status = 1;
    Node *p = root;
    while (p) {
    // 用来状态转移
        switch (status) {
            case 1: {
                while (p->ltag == NORMAL && p->lchild) p = p->lchild;
                status = 2;
            } break;
            case 2:  {
                printf("%d ", p->key);
                status = 3;
            } break;
            case 3: {
                if (p->rtag == NORMAL) {
                    status = 1;
                } else {
                    status = 2;
                }
                // 注意 先进行状态转移,再对p进行赋值
                p = p->rchild;
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
    build(root);
    output_thread(root);
    output(root);
    clear(root);
    return 0;
}
