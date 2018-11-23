/*************************************************************************
	> File Name: testcase4.h
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月09日 星期二 16时08分06秒
 ************************************************************************/

#ifndef _TESTCASE4_H
#define _TESTCASE4_H
#include "binary.h"
TEST(test, binary) {
    EXPECT(binary(4), 2);
    for (int i = 0; i < 100; i++) {
        EXPECT(binary(i), i);
    }
    //ASSERT(binary(1), 1);
}
#endif
