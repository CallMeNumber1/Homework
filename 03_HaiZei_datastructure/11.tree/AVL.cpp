/*************************************************************************
	> File Name: AVL.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年02月05日 星期二 22时11分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int key;
    int height;                          // 用高度来控制平衡
    struct Node *lchild, *rchild;
} Node;

Node *NIL;                              // 虚拟节点


Node *init(int key) {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->key = key;
    p->height = 1;
    p->lchild = p->rchild = NIL;        // 新建节点孩子指向NIL
    return p;
}

__attribute((constructor))              // 全局只运行一次
void init_NIL() {
    NIL = init(0);
    NIL->height = 0;
    NIL->lchild = NIL->rchild = NIL;    // 左右孩子指向自己
    return ;
}

void calc_height(Node *root) {
    root->height = max(root->lchild->height, root->rchild->height) + 1;
}

// 返回旋转完后新的根节点地址
Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->lchild = temp->lchild;
    temp->lchild = root;
}

Node *maintain(Node *root) {
    if (abs(root->lchild->height - root->rchild->height) <= 1) return root;
    // L型
    if (root->lchild->height > root->rchild->height) {
        // LR型 小左旋后大右旋
        if (root->lchild->lchild->height < root->lchild->rchild->height) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        
    }
}

Node *insert(Node *root, int key) {
    if (root == NULL) return init(key);
    if (root->key == key) return root;
    else if (root->key < key) root->rchild = insert(root->rchild, key);
    else root->lchild = insert(root->lchild, key);
    // 使用了虚拟节点，则不用特殊判断左右子树为空的情况了
    return maintain(root);
}


void clear(Node *node) {
    if (node == NULL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}
int main() {




    return 0;
}
