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
    FuncData ret;
    ret.next = NULL;
    for (FuncData *p = FuncData_head,*q; p; p = q) {
        q = p->next;
        p->next = ret.next;
        ret.next = p;
    }
    FuncData_head = ret.next;
    char color[3][100] = {
        "[ \033[1;32m%.2lf%% \033[0m] total : %d expect : %d\n",
        "[ \033[0;31m%.2lf%% \033[0m] total : %d expect : %d\n",
        "[ \033[1;31m%.2lf%% \033[0m] total : %d expect : %d\n",
    };
    for (FuncData *p = FuncData_head; p; p = p->next) {
        TestFuncData data = {0, 0};
        printf("[%s %s]\n", p->a_str, p->b_str);
        p->func(&data);
        double rate = 1.0 * data.expect / data.total * 100;
        int ind = 0;
        if (rate < 100) ind = 1;
        if (rate < 50) ind = 2;
        printf(color[ind], 1.0 * data.expect / data.total * 100, data.total, data.expect);
    }
    return 0;
} 

