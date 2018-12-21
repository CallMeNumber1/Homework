/*************************************************************************
	> File Name: testcase3.h
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月08日 星期一 22时18分20秒
 ************************************************************************/

#ifndef _TESTCASE3_H
#define _TESTCASE3_H
#include <math.h>
//为何包含math.h库后仍然提示对sqrt未定义的引用
#include "newtown.h"
TEST(test, newton) {
    //ASSERT(newtown(3, f1, f1_prime), 1);
    for (int i = 0; i < 100; i++) {
        EXPECT(newtown(i, f1, f1_prime), i);
    }
}
#endif
