/*************************************************************************
	> File Name: test.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月21日 星期日 15时37分02秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 0x3f3f3f3f
long long calc(const char *str, int l, int r) {
    int pos = -1, temp_prior = 0, prior = INF - 1;
    for (int i = l; i <= r; i++) {
        int cur_prior = INF;
        switch (str[i]) {
            case '+' : cur_prior = temp_prior + 1; break;
            case '*' : cur_prior = temp_prior + 2; break;
        }
        if (cur_prior <= prior) {
            prior = cur_prior;
            pos = i;
        }
    }
    if (pos == - 1) {
        long long num = 0;
        for (int i = l; i <= r; i++) {
            num = num * 10 + str[i] - '0';
        }
        return num;
    } else {
        long long a = calc(str, l, pos - 1);
        long long b = calc(str, pos + 1, r);
        switch (str[pos]) {
            case '+' : return (a + b) % 10000;
            case '*' : return (a * b) % 10000;
        }

    }
    return 0;
}

int main() {
    char str[500005];
    scanf("%s", str);
    //printf("%s = %d\n", str, calc(str, 0, strlen(str) - 1));
    long long ans = calc(str, 0, strlen(str) - 1) % 10000;
    printf("%lld\n", ans);
    return 0;
}


