/*************************************************************************
	> File Name: 1.left.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月13日 星期六 15时30分45秒
 ************************************************************************/

#include <stdio.h>
#define MAX 105
int main() {
    int n, k, temp;
    int data[MAX];
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        data[(i - k + n) % n] = temp;
    }
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", data[i]);
    }
    printf("%d\n", data[n - 1]);
}

