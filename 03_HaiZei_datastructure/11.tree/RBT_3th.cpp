/*************************************************************************
	> File Name: RBT_3th.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年02月23日 星期六 15时57分51秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1
#define DOUBLE_BLACK 2

typedef struct RBTNode {
    int key, color;
    struct RBTNode *lchild, *rchild;
} RBTNode;
RBTNode *NIL;

__attribute__((constructor))
void init_NIL() {
    NIL = (RBTNode *)malloc(sizeof(RBTNode));
    NIL->key = -1;
    NIL->color = BLACK;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}
RBTNode *init(int key) {
    RBTNode *p = (RBTNode *)malloc(sizeof(RBTNode));
    p->color = RED;
    p->key = key;
    p->lchild = p->rchild = NIL;
    return p;
}
int has_red_child(RBTNode *root) {
    return (root->lchild->color == RED || root->rchild->color == RED);
}

RBTNode *left_rotate(RBTNode *root) {
    RBTNode *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}
RBTNode *right_rotate(RBTNode *root) {
    RBTNode *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

RBTNode *insert_maintain(RBTNode *root) {
    if (!has_red_child(root)) return root;
    if (root->lchild->color == RED && root->rchild->color == RED) {
        if (!has_red_child(root->lchild) && !has_red_child(root->rchild)) return root;
    } else if (root->lchild->color == RED && has_red_child(root->lchild)) {
        if (root->lchild->rchild->color == RED) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else if (root->rchild->color == RED && has_red_child(root->rchild)) {
        if (root->rchild->lchild->color == RED) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    } else {
        return root;
    }
    root->color = RED;
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

RBTNode *__insert(RBTNode *root, int key) {
    if (root == NIL) return init(key);                              // 0.返回一个新建节点
    if (root->key == key) return root;
    if (root->key > key) {
        root->lchild = __insert(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
}

RBTNode *insert(RBTNode *root, int key) {
    root = __insert(root, key);
    root->color = BLACK;
    return root;
}

// 15min done

RBTNode *predecessor(RBTNode *root) {
    RBTNode *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

RBTNode *erase_maintain(RBTNode *root) {
    if (root->lchild->color != DOUBLE_BLACK && root->rchild->color != DOUBLE_BLACK) return root;
    #define UNBALANCE(a, b)  (root->a->color == DOUBLE_BLACK && root->b->color == BLACK && !has_red_child(root->b))
    if (UNBALANCE(lchild, rchild) || UNBALANCE(rchild, lchild)) {
        root->color += 1;
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        return root;
    }
    #undef UNBALANCE
    if (root->lchild->color == DOUBLE_BLACK) {
        if (root->rchild->color == RED) {
            root = left_rotate(root);
            root->color = BLACK;
            root->lchild->color = RED;
            root->lchild = erase_maintain(root->lchild);
            return root;
        }
        root->lchild->color = BLACK;                        //　1.消去双重黑
        if (root->rchild->rchild->color != RED) {
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK;
            root->rchild->rchild->color = RED;
        }
        root = left_rotate(root);
        root->color = root->lchild->color;
    } else {
        if (root->lchild->color == RED) {
            root = right_rotate(root);
            root->color = BLACK;
            root->rchild->color = RED;
            root->rchild = erase_maintain(root->rchild);
            return root;
        }
        root->rchild->color = BLACK;
        if (root->lchild->lchild->color != RED) {
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = BLACK;
            root->lchild->lchild->color = RED;
        }
        root = right_rotate(root);
        root->color = root->rchild->color;
    }
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

RBTNode *__erase(RBTNode *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) {
        root->lchild = __erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = __erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            RBTNode *temp = (root->lchild == NIL ? root->rchild : root->lchild);
            temp->color += root->color;                             // 2.！！！
            free(root);
            return temp;
        } else {
            RBTNode *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);        // 3.后面不能直接return root　因为还要站在根节点去调整
        }
    }
    return erase_maintain(root);
}

RBTNode *erase(RBTNode *root, int key) {
    root = __erase(root, key);
    root->color = BLACK;
    return root;
}

// 20min done
