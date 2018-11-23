/*************************************************************************
	> File Name: function.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月20日 星期四 22时29分59秒
 ************************************************************************/
// 变参函数演示
// 函数定义放在unit.c中 编译时一起编译
#include <stdio.h>

#define P(func) { \
    printf("%s = %d\n", #func, func); \
}
int is_prime(int x);
int max_int(int n, ...);

int main() {
    for (int i = 2; i <= 100; i++) {
        if (is_prime(i)) printf("%d\n", i);
    }
    P(max_int(3, 1, 2, 3));
    P(max_int(4, 1, 2, 3, 9));
    P(max_int(5, 1, 12, 3, 9, 10));
    return 0;
}
