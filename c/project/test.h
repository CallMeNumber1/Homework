/*************************************************************************
	> File Name: test.h
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月06日 星期六 10时14分58秒
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H
#include <stdlib.h>
typedef struct TestFuncData {
    int total, expect;
}TestFuncData;

typedef void (*test_func_t)(TestFuncData *);

typedef struct FuncData {
    const char *a_str, *b_str;
    test_func_t func;
    struct FuncData *next;
}FuncData;


void addFuncData(
    const char *a,
    const char *b,
    test_func_t func
);



#define TEST(a, b) \
    void a##_haizeix_##b(TestFuncData *); \
    __attribute__((constructor)) \
    void ADDFUNC_##a##_haizeix_##b() { \
        addFuncData(#a, #b, a##_haizeix_##b); \
    } \
    void a##_haizeix_##b(TestFuncData *_data)

#define EXPECT(a, b) ({ \
    int temp; \
    printf("%s = %s %s\n", #a, #b, (temp = (a == b)) ? "True" : "False"); \
    _data->total++; \
    _data->expect += temp; \
})

int RUN_ALL_TEST();

#endif
