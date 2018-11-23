/*************************************************************************
	> File Name: fun02.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月20日 星期四 18时44分14秒
 ************************************************************************/

#include <stdio.h>

int f(int x) {
    if (x == 1 || x == 0) return 1;
    return x * f(x - 1);
}
int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", f(n));
    return 0;
}
