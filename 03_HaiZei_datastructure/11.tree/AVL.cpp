/*************************************************************************
	> File Name: AVL.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年02月05日 星期二 22时11分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define max(a, b) ({ \
    __typeof(a) __a = (a); \
    __typeof(b) __b = (b); \
    __a > __b ? __a : __b; \
})
typedef struct Node {
    int key;
    int height;                          // 用高度来控制平衡
    struct Node *lchild, *rchild;
} Node;

Node *NIL = NULL;                              // 虚拟节点


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
    return ;
}

// 返回旋转完后新的根节点地址
Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    calc_height(root);
    calc_height(temp);
    return temp;
}
Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    calc_height(root);
    calc_height(temp);
    return temp;
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
         if (root->rchild->rchild->height < root->rchild->lchild->height) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root, int key) {
    // 我们的AVL树中是没有空节点的
    if (root == NIL) return init(key);
    if (root->key == key) return root;
    else if (root->key < key) root->rchild = insert(root->rchild, key);
    else root->lchild = insert(root->lchild, key);
    // 使用了虚拟节点，则不用特殊判断左右子树为空的情况了
    calc_height(root);
    return maintain(root);
}

// 前驱是左子树的最右节点
Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}
Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key < key) {
        root->rchild = erase(root->rchild, key);
    } else if (root->key > key) {
        root->lchild = erase(root->lchild, key);
    } else {
        // 度为0时 直接删除当前节点 
        if (root->lchild == NIL && root->rchild == NIL) {
            free(root);
            return NIL;
        } else if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = (root->lchild != NIL ? root->lchild : root->rchild);
            free(root);
            return temp;
        } else {
            // 度为2时
            Node *temp = predecessor(root);
            root->key = temp->key;
            // 去左子树删除一个值为temp->key的节点
            root = erase(root->lchild, temp->key);
        }   
    }
    calc_height(root);
    return maintain(root);
}

void clear(Node *node) {
    if (node == NIL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d, %d, %d)\n", root->key, root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
}
int main() {
    int op, val;
    Node *root = NIL;
    while (scanf("%d%d", &op, &val) != EOF) {
        switch (op) {
            case 1 : root = insert(root, val); break;
            case 2 : root = erase(root, val); break;
        }
        output(root);
    }
    return 0;
}
