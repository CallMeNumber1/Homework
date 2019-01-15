/*************************************************************************
	> File Name: calc.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月15日 星期二 22时30分18秒
 ************************************************************************/
/*
 逆波兰式
 此题目只含有 + - * / 不含括号
 船长小花招
 即程序的结构，逐层剥开
*/

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;


// 连续的数字优先级最高
// 优先级最高的套在最里面
int getNum(char *str, int *ret) {
    int i = 0, num = 0;
    while (str[i] <= '9' && str[i] >= '0') {
        num = num * 10 + str[i++] - '0';
    }
    *ret = num;
    return i;
}

// 处理乘法表达式
// 要知道处理了多少个字符，才知道下一次处理哪个term
int getTerm(char *str, int *ret) {
    int i = 0, temp;
    if (str[i] == 0) return 0;
    i += getNum(str + i, ret);
    if (str[i] == 0) return i;
    while (str[i]) {
        // 结果写入a, 返回的是处理了多少字符
        switch (str[i]) {
            case '*': {
                // 因为后面可能是连乘
                // 加1是当前符号位
                i += getNum(str + i + 1, &temp) + 1;
                (*ret) *= temp;
            } break;
            case '/': {
                i += getNum(str + i + 1, &temp) + 1;
                (*ret) /= temp;
            } break; 
            default: return i;
        }
    }
    return i;
}


// 给定一个表达式，计算值
// getTerm 乘法表达式和除法表达式称为Term 即处理乘除法
// calc处理加减法
int calc(char *str) {
    int i = 0, a, b;
    char op;
    while (str[i]) {
        i += getTerm(str + i, &a);
        // 还没有到最后
        if (str[i] == 0) return a;
        while (str[i]) {
            op = str[i];
            i += getTerm(str + i + 1, &b) + 1;
            switch (op) {
                // 刚开始那种写法，看似是bug，其实可作为功能
                // case'+': return a+calc(str + i + 1)
                // 正好可以实现运算符右结合的情况
                case '+': a += b; break;
                case '-': a -= b; break;
            }
        }   
    }
    return a;
}


int main() {
    char str[1000];
    scanf("%s", str);
    printf("%d\n", calc(str));


    return 0;
}

