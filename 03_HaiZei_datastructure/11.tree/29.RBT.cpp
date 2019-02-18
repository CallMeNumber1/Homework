/*************************************************************************
	> File Name: 29.RBT.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年02月17日 星期日 18时08分10秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BLACK 1
#define DOUBLE_BLACK 2
typedef int color_t;

typedef struct RBTNode {
    int key;         // 0 red, 1 black, 2 double black
    color_t color;
    struct RBTNode *lchild, *rchild;
} RBTNode;

RBTNode *NIL;

__attribute__((constructor))
void init_NIL() {
    NIL = (RBTNode *)malloc(sizeof(RBTNode));
    NIL->key = -1;
    NIL->color = BLACK;
    NIL->rchild = NIL->lchild = NIL;
    return ;
}

RBTNode *init(int key) {
    RBTNode *p = (RBTNode *)malloc(sizeof(RBTNode));
    p->key = key;
    p->lchild = p->rchild = NIL;
    p->color = RED;
    return p;
}

void clear(RBTNode *node) {
    if (node == NIL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
}

int has_red_child(RBTNode *root) {
    return (root->lchild->color == RED || root->rchild->color == RED);
}

RBTNode *left_rotate(RBTNode *node) {
    RBTNode *temp = node->rchild;
    node->rchild = temp->lchild;
    temp->lchild = node;
    return temp;
}

RBTNode *right_rotate(RBTNode *node) {
    RBTNode *temp = node->lchild;
    node->lchild = temp->rchild;
    temp->rchild = node;
    return temp;
}

RBTNode *insert_maintain(RBTNode *root) {
    // 没有红色孩子 不可能失衡
    if (!has_red_child(root)) return root;
    if (root->lchild->color == RED && root->rchild->color == RED) {
        // 加不加不影响平衡性
        // 即使任性改了颜色也不会冲突
        // 考试时不能删去，因为失衡了才能改颜色
        //if (!has_red_child(root->lchild) && !has_red_child(root->rchild)) return root;
        // 最好改的一种情况
    } else if (root->lchild->color == RED && has_red_child(root->lchild)) {
        // LL or LR ?
        if (root->lchild->rchild->color == RED) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
        // 开始改颜色 两种方法
        // 此时使用红色上顶
        // (右旋后两个孩子一定是黑色的。。)
    } else if (root->rchild->color == RED && has_red_child(root->rchild)) {
        if (root->rchild->lchild->color ==  RED) {
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
    if (root == NIL) return init(key);
    if (root->key == key) return root;
    else if (root->key > key) {
        root->lchild = __insert(root->lchild, key);
    } else {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
    // 向下到底后，逐层向上回溯调整。。。。
}
// 包装一层insert来保证根节点一定是黑色(整个树的根节点)
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
    if (root->lchild->color != DOUBLE_BLACK && root->rchild->color != DOUBLE_BLACK) return root;
    /*
     * 此段代码可以代替下面两个if条件
    #define UNBALANCE(a, b) (root->a->color = DOUBLE_BLACK && !has_red_child(root->b))
    if (UNBALANCE(lchild, rchild) || UNBALANCE(rchild, lchild)) {
        root->color += 1;
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        return root;
    }
    */
    if (root->lchild->color == DOUBLE_BLACK) {
        // 兄弟为红色
        if (root->rchild->color == RED) {
            root = left_rotate(root);
            // 左旋后需要改变颜色
            root->color = BLACK;
            root->lchild->color = RED;
            // 变成了兄弟节点为黑色的情况
            // 递归到子节点去处理
            return erase_maintain(root->lchild);
        }
        // 到了这一行 代表兄弟节点为黑色
        if (!has_red_child(root->rchild)) {
            // 情况一
            root->color += 1;
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            return root;

        }
        // 去掉双重黑
        // 因为经过下面调整 肯定可以平衡
        root->lchild->color = BLACK;
        // 到了这一行，说明兄弟节点有红色孩子
        if (root->rchild->rchild->color != RED) {
            // 充分 判断RL型 即情况二
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK;
            root->rchild->rchild->color = RED;
        }
        // 情况三
        root = left_rotate(root);
        root->color = root->lchild->color;  // 等于原来根节点颜色
    } else {
        if (root->rchild->color == RED) {
            root = right_rotate(root);
            root->color = BLACK;
            root->rchild->color = RED;
            return erase_maintain(root->rchild);
        }
        if (!has_red_child(root->lchild)) {
            root->color += 1;
            root->rchild->color -= 1;
            root->lchild->color -= 1;
            return root;
        }
        root->rchild->color = BLACK;
        // 到了这一行，说明兄弟节点有红色孩子
        if (root->rchild->rchild->color != RED) {
            // 充分 判断RL型
            root->lchild = left_rotate(root->rchild);
            root->lchild->color = BLACK;
            root->lchild->lchild->color = RED;
        }
        root = right_rotate(root);
        root->color = root->rchild->color;  // 等于原来根节点颜色
    }
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

// 保证删除操作后根节点为黑色（因为可能成为双重黑)
RBTNode *__erase(RBTNode *root, int key) {
    if (root == NIL) return NIL;
    if (root->key > key) {
        root->lchild = __erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = __erase(root->rchild, key);
    } else {
        // 同时处理度为0和度为1的情况 （将两种情况合并了）
        if (root->lchild == NIL || root->rchild == NIL) {
            RBTNode *temp = (root->lchild == NIL ? root->rchild : root->lchild);
            // 将当前节点颜色加到子孩子
            // 为了保持平衡
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            RBTNode *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}
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
int main() {
    srand(time(0));
    int op, val;
    RBTNode *root = NIL;
    #define MAX_OP 20
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 3, val = rand() % 10;
        switch (op) {
            case 0: 
                printf("delete val %d from RBT\n", val);
                root = erase(root, val);
                break;
            case 1: 
            case 2:
                printf("insert val %d to RBT\n", val);
                root = insert(root, val);
                break;
        }
        output(root);
    }
    return 0;
}


