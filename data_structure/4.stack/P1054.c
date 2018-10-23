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

int calc(const char *str, int l, int r, int a_value) {
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
        int num = 0;
        for (int i = l; i <= r; i++) {
            if (str[i] == 'a') return a_value;
            if (str[i] < '0' || str[i] > '9') continue;
            num = num * 10 + str[i] - '0';
        }
        return num;
    } else {
        int a = calc(str, l, pos - 1, a_value);
        int b = calc(str, pos + 1, r, a_value);
        switch (str[pos]) {
            case '+' : return a + b;
            case '-' : return a - b;
            case '*' : return a * b;
            case '/' : return a / b;
            case '^' : return (int)pow(a, b);
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
    scanf("%[^\n]s", str);
    scanf("%d", &num);
    getchar();
    len = strlen(str);
    for (int i = 0; i < num; i++) {
        scanf("%[^\n]s", opt[i]);
        getchar();              // 为什么不加getchar会报错
    }
    //printf("%s\n", str);
    //for (int i = 0; i < num; i++) {
    //    printf("%s\n", opt[i]);
    //}
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < 10; j++) {
            int value = rand() % 100;
            int dest = calc(str, 0, len - 1, value);
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

