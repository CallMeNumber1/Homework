/*************************************************************************
	> File Name: head.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月10日 星期四 20时27分45秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "head.h"
// 使用static是出于封装的目的，只能在当前文件夹下使用
static int virtual_demo_add(demo *pthis, int v);
static int virtual_derived_add(derived *pthis, int v);

// 结构体中存的是虚函数地址（指向虚函数表）
typedef struct vtable {
    int (*padd)(void *, int);
} vtable;
typedef struct class_demo {
    vtable *vptr;
    int i;
    int j;
} class_demo;

typedef struct class_derived {
    class_demo d;
    int k;
} class_derived;


// 给虚函数表赋值（指明虚函数表里的函数）
static vtable g_classdemo_vptr =  {
    virtual_demo_add
};
static vtable g_classderived_vptr = {
// 给padd成员变量赋值
    virtual_derived_add
};

demo *demo_init(int i, int j) {
    class_demo *p = (class_demo *)malloc(sizeof(class_demo));
    if (p != NULL) {
        p->vptr = &g_classdemo_vptr;
        p->i = i;
        p->j = j;
    }
    return p;
}
int getI(demo *pthis) {
    class_demo *p = (class_demo *)pthis;
    return p->i;
}
int getJ(demo *pthis) {
    class_demo *p = (class_demo *)pthis;
    return p->j;
}

// 5.定义虚函数表中指针指向的具体函数
static int virtual_demo_add(demo *pthis, int v) {
    class_demo *p = (class_demo *)pthis;
    return p->i + p->j + v;
}

// 4.分析具体的虚函数是做什么的
int demo_add(demo *pthis, int v) {
    class_demo *p = (class_demo *)pthis;
    return p->vptr->padd(pthis, v);
}

void demo_free(demo *pthis) {
    free(pthis);
    return ;
}

derived *derived_init(int i, int j, int k) {
    class_derived *p = (class_derived *)malloc(sizeof(class_derived));
    if (p != NULL) {
        // 3.关联对象与虚函数表
        p->d.vptr = &g_classderived_vptr;
        class_demo *p2 = (class_demo *)p;
        printf("demo:%p derived:%p\n", p2->vptr, p->d.vptr);
        p->d.i = i;
        p->d.j = j;
        p->k = k;
    }
    return p;
}

int getK(derived *pthis) {
    class_derived *p = (class_derived *)pthis;
    return p->k;
}
static int virtual_derived_add(derived *pthis, int v) {
    class_derived *p = (class_derived *)pthis;
    return p->d.i + p->d.j + p->k + v;
}

int derived_add(derived *pthis, int v) {
    class_derived *p = (class_derived *)pthis;
    return p->d.vptr->padd(pthis, v);
}

void derived_free(derived *pthis) {
    free(pthis);
    return ;
}
