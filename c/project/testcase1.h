/*************************************************************************
	> File Name: testcase1.h
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月07日 星期日 12时30分15秒
 ************************************************************************/

#ifndef _TESTCASE1_H
#define _TESTCASE1_H
#include "test.h"
#include "is_prime.h"
TEST(test, is_prime_func) {
    EXPECT(is_prime(2), 0);
    EXPECT(is_prime(-2), 0);
    EXPECT(is_prime(15), 0);
    EXPECT(is_prime(9973), 1);
}

#endif
