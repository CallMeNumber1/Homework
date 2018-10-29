/*************************************************************************
	> File Name: a.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月28日 星期日 20时00分54秒
 ************************************************************************/

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    int key, freq;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key, int freq) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->freq = freq;
    p->lchild = p->rchild = NULL;
    return p;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}
// p,q为指向地址的指针,被指向的地址再指向Node
// 将p指向的地址与q指向的地址交换
void swap_node(Node **p, Node **q) {
    Node *temp = *p;
    *p = *q;
    *q = temp;
    return ;
}
Node *build_haffman(Node **arr, int n) {
    Node INIT_NODE = {0, INT32_MAX, NULL, NULL};
    // 外层循环:合并n-1次
    for (int i = 0; i < n - 1; i++) {   
        for (int j = 0; j < n - i - 2; j++) {
            if (arr[j]->freq < arr[n - i - 1]->freq) {
                swap_node(arr + j, arr + n - i - 1);
            } 
            if (arr[j]->freq < arr[n - i - 2]->freq) {
                //printf("before: %c->%d %c->%d\n", arr[j]->key, arr[j]->freq, arr[n - i - 2]->key, arr[n - i - 2]->freq);
                swap_node(arr + j, arr + n - i - 2);
                //printf("after: %c->%d %c->%d\n", arr[j]->key, arr[j]->freq, arr[n - i - 2]->key, arr[n - i - 2]->freq);
            }
        }
        // 每次把出现频次最小的两个数放在后两个位置,后一个位置放最小的
        // 即例如i=0时,最小的两个数放在4,5两个位置
        // 之后将这两个位置中的前一个覆盖,保存两个节点合并所得到的节点
        Node *temp = getNewNode(0, arr[n - i - 1]->freq + arr[n - i - 2]->freq);
        // 船长的代码没有下面这个语句
        // 此语句用来保证左孩子的频次一定小于右孩子
        if (arr[n - i - 1]->freq > arr[n - i - 2]->freq) {
            swap_node(arr + n - i - 1, arr + n - i - 2);
        }
        temp->lchild = arr[n - i - 1];
        temp->rchild = arr[n - i - 2];
        arr[n - i - 2] = temp;
    }
    // 最后得到的arr数组中,依次存储了每一层的一个节点(用来合并的较小节点)
    for (int i = 0; i < n; i++) {
        printf("%c->%d\n", arr[i]->key, arr[i]->freq);
    }
    return arr[0];
}

void extract_code(Node *root, char (*code)[20], int k, char *buff) {
    buff[k] = 0;
    // 当前节点的key不为0,即为叶子节点时,将编码buff储存到code数组的相应位置
    if (root->key) {
        strcpy(code[root->key], buff);
        return ;
    }
    // 左0右1.从第0层(根节点)开始往下走,编码为'0'往左子树走,编码为'1'往右子树走
    buff[k] = '0';
    extract_code(root->lchild, code, k + 1, buff);
    buff[k] = '1';
    extract_code(root->rchild, code, k + 1, buff);
    return ;

}
int main() {
    int n;
    Node **arr = (Node **)malloc(sizeof(Node *) * n);
    Node *root;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char key[10];   //方便处理
        int freq;
        scanf("%s%d", key, &freq);
        arr[i] = getNewNode(key[0], freq);
    }
    root = build_haffman(arr, n);
    char code[256][20] = {0}, buff[20];
    // 要传递层号进去,第i层编码对应原字符编码的第i位
    extract_code(root, code, 0, buff);
    for (int i = 0; i < 256; i++) {
        if (code[i][0] == 0) continue;
        printf("%c : %s\n", i, code[i]);
    }
    return 0;
}

