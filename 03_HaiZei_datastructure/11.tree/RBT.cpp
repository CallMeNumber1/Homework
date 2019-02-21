/*************************************************************************
	> File Name: RBT.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年02月19日 星期二 12时14分25秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RED 0
#define BLACK 1
#define DOUBLE_BLACK 2

typedef struct RBTNode {
    int key, color;
    struct RBTNode *lchild, *rchild;
} RBTNode;
RBTNode *NIL;
void init_NIL() {
    NIL = (RBTNode *)malloc(sizeof(RBTNode));
    NIL->key = -1;
    NIL->color = BLACK;
    NIL->lchild = NIL;
    NIL->rchild = NIL;
    return ;
}
RBTNode *init(int key) {
    RBTNode *p = (RBTNode *)malloc(sizeof(RBTNode));
    p->key = key;
    p->color = RED;
    p->lchild = NIL;
    p->rchild = NIL;
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
        /*
        if (!has_red_child(root->lchild) && !has_red_child(root->rchild)) {
            // 如果两个红色孩子下面都没有红色孩子 则不需要调整
            return root;
        }
        */
    } else if (root->lchild->color == RED && has_red_child(root->lchild)) {
        // 旋转之后戴顶小帽子即可
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
        // root有红色孩子 但红色孩子下面没有红色孩子 则直接返回
        return root;
    }
    // 戴顶小帽子的操作：此处使用红色上顶
    root->color = RED;
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}


RBTNode  *__insert(RBTNode *root, int key) {
    if (root == NIL) return init(key);
    if (root->key == key) return root;          // 相等时不插入
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

RBTNode *predecessor(RBTNode *root) {
    RBTNode *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

RBTNode *erase_maintain(RBTNode *root) {
    // 没有双重黑时不必调整
    if (root->lchild->color != DOUBLE_BLACK && root->rchild->color != DOUBLE_BLACK) return root;
    // 右孩子为双重黑
    if (root->rchild->color == DOUBLE_BLACK) {
        // 兄弟节点是红色时
        if (root->lchild->color == RED) {
            root = right_rotate(root);
            root->color = BLACK;
            root->rchild->color = RED;
            return erase_maintain(root->rchild);
        }
        // 兄弟节点是黑色
        if (!has_red_child(root->lchild)) {                 // ！！！情况一
            root->color += 1;
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            return root;
        }
        root->rchild->color = BLACK;                        // ！！！经过下面的调整肯定会消除双重黑,别忽略此句
        if (root->lchild->lchild != RED) {                  // 判断情况二LR型
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = BLACK;
            root->lchild->lchild->color = RED;
        }
        root = right_rotate(root);                          // 情况三
        root->color = root->rchild->color;
        root->lchild->color = root->rchild->color = BLACK;
    } else {
        // 兄弟为红
        if (root->rchild->color == RED) {
            root = left_rotate(root);
            root->color = BLACK;
            root->lchild->color = RED;
            return erase_maintain(root->lchild);
        }
        // 兄弟为黑
        if (!has_red_child(root->rchild)) {
            root->color += 1;
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            return root;
        }
        root->lchild->color = BLACK;                        // ！！！一定记得去除双重黑
        if (root->rchild->rchild != RED) {                  // 判断为情况二的RL型
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK;
            root->rchild->rchild->color = RED;
        }
        root = left_rotate(root);
        root->color = root->lchild->color;
        root->lchild->color = root->rchild->color = BLACK;
    }
    return root;
}

RBTNode *__erase(RBTNode *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) {
        root->lchild = __erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = __erase(root->rchild, key);
    } else {
        // 度为0或1的情况
        if (root->lchild == NIL || root->rchild == NIL) {
            RBTNode *temp = (root->lchild == NIL ? root->rchild : root->lchild);
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            RBTNode *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);                // ！！！替换之后，删除值为前驱的值的元素
        }
    }
    return erase_maintain(root);
}

// 维护红黑树的第一条性质
RBTNode *erase(RBTNode *root, int key) {
    root = __erase(root, key);
    root->color = BLACK;
    return root;
}


void output(RBTNode *root) {
    if (root == NIL) return ;
    printf("(%d %d %d) = %d\n", root->key, root->lchild->key, root->rchild->key, root->color);
    output(root->lchild);
    output(root->rchild);
    return ;
}
void clear(RBTNode *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}


int main() {
    init_NIL();                 // ！！！！别忘记调用
    int op, val;
    RBTNode *root = NIL;
    while (scanf("%d%d", &op, &val) != EOF) {
        switch (op) {
            case 1: {
                printf("insert %d to RBT\n", val);
                root = insert(root, val);
            } break;
            case 2: {
                printf("delete %d from RBT\n", val);
                root = erase(root, val);
            }
        }
        output(root);
    }
    return 0;
}
