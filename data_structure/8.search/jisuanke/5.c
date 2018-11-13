/*************************************************************************
	> File Name: 5.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月08日 星期四 22时23分56秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, temp;
    scanf("%d", &n);
    int *num = (int *)calloc(sizeof(int), n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        if (temp > 0 && temp <= n) {
            num[temp] = 1;
        }
    }
    int ans;
    for (int i = 1; i <= n; i++) {
        if (num[i] == 0) {
            ans = i;
            break;
        }
    }
    printf("%d\n", ans);
    free(num);
    return 0;
}

