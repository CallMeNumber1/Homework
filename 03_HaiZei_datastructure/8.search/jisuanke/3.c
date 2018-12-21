/*************************************************************************
	> File Name: 3.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月08日 星期四 15时31分08秒
 ************************************************************************/

#include <stdio.h>
#define MAX 505
int main() {
    int n, target, num[MAX];
    int hash[1005] = {0};  
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &num[i]);
    }
    scanf("%d", &target);
    for (int i = 1; i <= n; i++) {
        if (num[i] <= target && hash[target - num[i]]) {
            printf("%d %d\n", hash[target - num[i]], i);
            break ;
        }
        hash[num[i]] = i;
    }
    return 0;
}

