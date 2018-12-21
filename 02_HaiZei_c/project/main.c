/*************************************************************************
	> File Name: main.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月07日 星期日 11时25分13秒
 ************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "is_prime.h"
#include "add.h"
#include "newtown.h"
#include "test.h"
#ifdef TEST_FUNC
    #include "testcase1.h"
    #include "testcase2.h"
    #include "testcase3.h"
    #include "testcase4.h"
#endif

int main() {
    printf("hello world\n");
    is_prime(5);
    add(2, 2);
    RUN_ALL_TEST();
}
