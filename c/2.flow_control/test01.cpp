/*************************************************************************
	> File Name: test01.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月18日 星期二 18时30分01秒
 ************************************************************************/

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    if (n == 0) {
        printf("FOOLISH\n");
    } else if (n < 60) {
        printf("FALL\n");
    } else if (n < 75) {
        printf("MEDIUM\n");
    } else if (n <= 100) {
        printf("GOOD\n");
    } else {
        printf("ERROR\n");
    }
    return 0;
}
