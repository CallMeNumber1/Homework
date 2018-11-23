/*************************************************************************
	> File Name: test.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月07日 星期日 14时32分00秒
 ************************************************************************/

#include <stdio.h>
#include "test.h"
FuncData *FuncData_head = NULL;

void addFuncData(
    const char *a,
    const char *b,
    test_func_t func
) {
    FuncData *p = (FuncData *)malloc(sizeof(FuncData));
    p->a_str = a;
    p->b_str = b;
    p->func = func;
    p->next = FuncData_head;
    FuncData_head = p;
    return ;
} 
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

