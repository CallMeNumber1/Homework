/*************************************************************************
	> File Name: P1981.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月21日 星期日 16时38分22秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAX_N 2300000
#define MOD_NUM 10000
char str[MAX_N];

int calc(char *str) {
    int len = strlen(str);
    //　用＋号将字符串分隔成几个部分
    for (int i = 0; str[i]; i++) str[i] = (str[i] == '+' ? 0 : str[i]);
    int total = 0;
    for (int j = 0; j < len; j += strlen(str + j) + 1) {
        int num = 0, p = 1;
        for (int i = j; str[i]; i++) {
            switch (str[i]) {
                case '*' : p *= num; p %= MOD_NUM; num = 0; break;
                default : num = num * 10 + str[i] - '0';
            }
        }
        p *= num; p %= MOD_NUM;
        total += p;
        total %= MOD_NUM;
    }
    return total;
}
int main() {
    while (scanf("%s", str) != EOF ) {
        printf("%d\n", calc(str));
        memset(str, 0, sizeof(str));
    }
    
    return 0;
}

