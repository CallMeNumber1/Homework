/*************************************************************************
	> File Name: union.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月04日 星期四 10时00分48秒
 ************************************************************************/
// 利用共用体将
#include <stdio.h>

union IP {
    struct {
        unsigned char arr[4];   //无符号的字符型能存的最大数字为255
    };
    unsigned int num;
};

int main() {
    int a, b, c, d;
    IP ip;
    while (scanf("%d.%d.%d.%d", &a, &b, &c, &d) != EOF) {
        ip.arr[0] = a;
        ip.arr[1] = b;
        ip.arr[2] = c;
        ip.arr[3] = d;
        printf("%d\n", ip.num);
    }

    return 0;
 }
