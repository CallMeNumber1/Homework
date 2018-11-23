/*************************************************************************
	> File Name: is_prime.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月07日 星期日 11时26分35秒
 ************************************************************************/

#include <stdio.h>
#include "is_prime.h"
#include "test.h"

int is_prime(int x) {
    if (x <= 1) return 0;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}
