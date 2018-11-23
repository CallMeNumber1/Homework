/*************************************************************************
	> File Name: sturct_union.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月04日 星期四 10时19分05秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include <stdio.h>

struct person {
    char name[20];
    int age;
    char gender;
    float height;
};

struct test {
    char a;
    char b;
    char c;
    int d;
};
int main() {
    struct test a;
    printf("sizeof(person):%d\n", sizeof(struct person));
    printf("%p %p %p %p\n", &a.a, &a.b, &a.c, &a.d);
    return 0;
}
