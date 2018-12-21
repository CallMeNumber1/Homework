/*************************************************************************
	> File Name: test02.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月18日 星期二 18时52分27秒
 ************************************************************************/
#include <stdio.h>

int main() {
    int n;
    while (scanf("%d", &n) != -1) {
        switch (n) {
            case 1: printf("one\n"); break;
            case 2: printf("two\n"); break;
            case 3: printf("three\n"); break;
            default: printf("error\n");
        }
    }
    
    return 0;
}
