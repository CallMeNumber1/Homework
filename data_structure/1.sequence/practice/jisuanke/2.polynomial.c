/*************************************************************************
	> File Name: 2.polynomial.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月13日 星期六 15时39分59秒
 ************************************************************************/

#include <stdio.h>
#include <math.h>
#define MAX 20

typedef struct Node {
    int c;
    int e;
} Node;
int main() {
    int m, x0;
    int ans = 0;
    Node data[MAX];
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &data[i].c, &data[i].e);
    }
    scanf("%d", &x0);
    for (int i = 0; i < m; i++) {
        ans += data[i].c * (int)pow(x0, data[i].e);
    }    
    printf("%d\n", ans);
    return 0;
}

