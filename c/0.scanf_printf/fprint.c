/*************************************************************************
	> File Name: print-1.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月13日 星期四 18时59分23秒
 ************************************************************************/
//只输出数的位数
//fprintf的用法

#include <stdio.h>

int main() {
    int n;
    FILE *fout = fopen("/dev/null", "w");
    while (scanf("%d", &n) != EOF) {
        printf("%d\n", fprintf(fout, "%d", n));
    }
    return 0;
}
