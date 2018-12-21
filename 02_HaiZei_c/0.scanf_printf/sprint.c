/*************************************************************************
	> File Name: print.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月13日 星期四 18时30分08秒
 ************************************************************************/

#include <stdio.h>
//打印一个数有几位
//sprintf的相关用法,返回值和printf一样,为打印字符的个数
int main() {
    int n;
    char str[100];
    while(scanf("%d", &n) != -1) {
        printf(" has %d digit\n", printf("%d", n));
        printf("%d\n", sprintf(str, "%d", n));
        printf("str = %s\n", str);
    }
    return 0;
}
