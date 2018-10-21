/*************************************************************************
	> File Name: 3.setIntersection.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月13日 星期六 15时58分14秒
 ************************************************************************/

#include <stdio.h>
#define MAX 55

int main() {
    int n, m;
    int la[MAX], lb[MAX], lc[MAX];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &la[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &lb[i]);
    }
    int p = 0, q = 0, k = 0;
    while (p < n && q < m) {
        if (la[p] == lb[q]) {
            lc[k++] = la[p];
            p++, q++;
        } else if (la[p] < lb[q]) {
            p++;
        } else if (la[p] > lb[q]) {
            q++;
        }
    }
    // 特判, 即没有相交的元素
    if (k == 0) {
        printf("%d\n", k);
        return 0;
    }
    printf("%d\n", k);
    for (int i = 0; i < k - 1; i++) {
        printf("%d ", lc[i]);
    }
    printf("%d\n", lc[k - 1]);
   return 0;
}

