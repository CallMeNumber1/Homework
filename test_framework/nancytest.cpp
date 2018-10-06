/*************************************************************************
	> File Name: nancytest.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月06日 星期六 15时14分46秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <vector>
#include "nancytest.h"
using namespace std;

int add(int a, int b) {
    return a + b;

}

int is_prime(int x) {
    if (x <= 1) return 0;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;    
    }
    return 1;

}

TEST(is_prime_func) {
        EXPECT(is_prime(2), 0);
        EXPECT(is_prime(-2), 0);
        EXPECT(is_prime(15), 0);
        EXPECT(is_prime(9973), 1);

}

TEST(add_func) {
        EXPECT(add(1, 2), 3);
        EXPECT(add(3, 4), 7);
        EXPECT(add(2, 2), 4);
}

int main(int argc, char* argv[])
{
    return RUN_ALL_TESTS();
}
