/*************************************************************************
	> File Name: fun01.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月20日 星期四 18时33分40秒
 ************************************************************************/
// K & R 风格函数
// gcc编译才行
#include<stdio.h>
int is_prime(x)
int x;
{
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}
int main() {
    int n;
    while (scanf("%d", &n) != -1) {
        if (is_prime(n)) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}
