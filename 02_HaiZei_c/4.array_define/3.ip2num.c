/*************************************************************************
	> File Name: 3.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月24日 星期一 11时08分53秒
 ************************************************************************/
//将IP地址转化为一个数字
#include<stdio.h>

int main() {
    unsigned int ret;
    unsigned char *p = (unsigned char *)&ret;
    int a, b, c, d;
    while (scanf("%d%d%d%d", &a, &b, &c, &d) != EOF) {
        p[0] = a;
        p[1] = b;
        p[2] = c;
        p[3] = d;
        printf("ret = %x\n", ret);
        printf("ret = %u\n", ret);
    }
    return 0;
}
