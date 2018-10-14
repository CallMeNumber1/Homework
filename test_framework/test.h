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

FuncData *FuncData_head = NULL;

FuncData *getFuncData(
    const char *a,
    const char *b,
    test_func_t func,
    FuncData *next
) {
    FuncData *p = (FuncData *)malloc(sizeof(FuncData));
    p->a_str = a;
    p->b_str = b;
    p->func = func;
    p->next = next;
    return p;
}

#define TEST(a, b) \
    void a##_haizeix_##b(TestFuncData *); \
    __attribute__((constructor)) \
    void ADDFUNC_##a##_haizeix_##b() { \
        FuncData_head = getFuncData(#a, #b, a##_haizeix_##b, FuncData_head); \
    } \
    void a##_haizeix_##b(TestFuncData *_data)

#define EXPECT(a, b) ({ \
    _data->total++; \
    printf("%s = %s %s\n", #a, #b, a == b ? "True" : "False"); \
    if (a == b) _data->expect++; \
})

int RUN_ALL_TEST() {
    //FuncData ret;
    //ret.next = NULL;
    //for (FuncData *p = FuncData_head; *q = p->next, p; p = q) {
    //    ret.next = p;
    //    ret = ret.next;
    //}
    for (FuncData *p = FuncData_head; p; p = p->next) {
        TestFuncData data = {0, 0};
        printf("[%s %s]\n", p->a_str, p->b_str);
        p->func(&data);
        if (data.total != data.expect) {
            printf("\033[1;31m[ FAIL ]\033[0m");
        } else {
            printf("\033[1;32m[ PASS ]\033[0m");
        }
        printf(" total = %d expect = %d\n", data.total, data.expect);
    }
    return 0;
}
#endif
