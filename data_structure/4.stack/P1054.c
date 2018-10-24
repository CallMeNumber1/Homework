/*************************************************************************
	> File Name: test.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月21日 星期日 15时37分02秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define INF 0x3f3f3f3f
#define MOD_NUM 100000000000
long long calc(const char *str, int l, int r, int a_value) {
    int pos = -1, temp_prior = 0, prior = INF - 1;
    for (int i = l; i <= r; i++) {
        int cur_prior = INF;
        switch (str[i]) {
            case '(' : temp_prior += 100; break;
            case ')' : temp_prior -= 100; break;
            case '+' : cur_prior = temp_prior + 1; break;
            case '-' : cur_prior = temp_prior + 1; break;
            case '*' : cur_prior = temp_prior + 2; break;
            case '/' : cur_prior = temp_prior + 2; break;
            case '^' : cur_prior = temp_prior + 3; break;
        }
        if (cur_prior <= prior) {   // 寻找优先级最小的操作符
            prior = cur_prior;
            pos = i;
        }
    }
    if (pos == - 1) {               // 当找到的不是操作符时,则为操作数
        long long num = 0;
        for (int i = l; i <= r; i++) {
            if (str[i] == 'a') return a_value;
            if (str[i] < '0' || str[i] > '9') continue;
            num = num * 10 + str[i] - '0';
        }
        return num;
    } else {
        long long a = calc(str, l, pos - 1, a_value);
        long long b = calc(str, pos + 1, r, a_value);
        switch (str[pos]) {
            case '+' : return (a + b + MOD_NUM) % MOD_NUM ;
            case '-' : return (a - b + MOD_NUM) % MOD_NUM ;
            case '*' : return (a * b) % MOD_NUM;
            case '/' : return (a / b) % MOD_NUM;
            case '^' : return (long long)pow(a, b) % MOD_NUM;
        }

    }
    return 0;
}


int main() {
    srand(time(0));
    char str[100];
    char opt[30][100];
    int num, len;
    int valid[30] = {0};
    scanf("%[^\r\n\t]s", str),getchar(), getchar();
    scanf("%d", &num);
    getchar(), getchar();
    len = strlen(str);
    for (int i = 0; i < num; i++) {
        scanf("%[^\r\n\t]s", opt[i]);
        getchar();              // 为什么不加getchar会报错
        getchar();
    }
    printf("%s\n", str);
    for (int i = 0; i < num; i++) {
        printf("%s\n", opt[i]);
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < 10; j++) {
            int value = rand() % 100 + 200;
            long long dest = calc(str, 0, len - 1, value);
            if (calc(opt[i], 0, strlen(opt[i]) - 1, value) != dest) {
                valid[i] = 1;
                break;
            }
        }  
    }
    for (int i = 0; i < num; i++) {
        if (valid[i] == 1) continue;
        printf("%c", i + 'A');
    }
    printf("\n");
    return 0;
}

