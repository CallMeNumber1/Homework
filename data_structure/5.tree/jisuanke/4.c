/*************************************************************************
	> File Name: 4.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月28日 星期日 18时57分56秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;


Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = NULL;
    p->rchild = NULL;
    return p;
}


int main() {
    char str[4];
    while (scannf("%s", str) != EOF) {
        if (str[0] == str[1] && str[0] == '^') break;
        
    }
    return 0;
}
