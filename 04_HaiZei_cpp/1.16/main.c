/*************************************************************************
	> File Name: main.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月10日 星期四 20时34分47秒
 ************************************************************************/

#include <stdio.h>
#include "head.h"

// 当传入class_derived类型时（子类），父类指针指向子类中的父类部分
// 因为子类的内存排布是是父类+自己的变量
void how_to_select(demo *p, int v) {
    int ret = demo_add(p, v);
    printf("res = %d\n", ret);
}

int main() {
    demo *p1 = demo_init(1, 2);
    derived *p2 = derived_init(1, 2, 3);
    printf("----demo output----\n");
    printf("i = %d, j = %d\n", getI(p1), getJ(p1));
    printf("add = %d\n", demo_add(p1, 5));
    
    printf("----derived output----\n");
    printf("i = %d, j = %d, k = %d\n", getI(p2), getJ(p2), getK(p2));
    how_to_select(p1, 1);
    how_to_select(p2, 1);
    demo_free(p1);
    derived_free(p2);
    return 0;
}
