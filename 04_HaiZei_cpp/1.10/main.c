/*************************************************************************
	> File Name: main.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月10日 星期四 20时34分47秒
 ************************************************************************/

#include <stdio.h>
#include "head.h"

int main() {
    demo *p = demo_init(1, 2);
    printf("a = %d, b = %d\n", getI(p), getJ(p));
    printf("add = %d\n", add(p, 5));
    return 0;
}
