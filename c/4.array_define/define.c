/*************************************************************************
	> File Name: define.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月23日 星期日 12时02分07秒
 ************************************************************************/

#include <stdio.h>

// 编译时加上-DDEBUG选项
// 条件编译
#ifdef DEBUG
#define P printf("%s : %d\n", __PRETTY_FUNCTION__, __LINE__)
#else
#define P
#endif

void testfunc() {
    P;
}
int main() {
    printf("%s %s\n", __DATE__, __TIME__);
    P;
    testfunc();
    return 0;
}
