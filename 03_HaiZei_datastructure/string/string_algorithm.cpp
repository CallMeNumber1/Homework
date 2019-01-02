/*************************************************************************
	> File Name: string_algorithm.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月02日 星期三 16时36分09秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST(func, a, b) { \
    printf("%s(%s, %s) = %d\n", #func, a, b, func(a, b)); \
} \


// 第一次出现位置, 否则-1
int BruteForce(char *str, char *pattern) {
    for (int i = 0; str[i]; i++) {
        int flag = 1;   // 可能成立
        for (int j = 0; pattern[j]; j++) {
            if (str[i + j] == pattern[j]) continue;
            flag = 0;
            break;
        }
        if (flag) return i;
    }    
    return -1;
}

int KMP(char *str, char *pattern) {
    int *next = (int *)malloc(sizeof(int) * strlen(pattern));
    next[0] = -1;
    // 初始化next数组
    for (int i = 1; pattern[i]; i++) {
        int j = next[i - 1];
        if (j != -1 && pattern[j + 1] != pattern[i]) j = next[j];
        if (pattern[j + 1] == pattern[i]) next[i] = j + 1;
        else next[i] = -1;    
    }
    int i = 0, j = -1;      
    // i指向待匹配的位置
    // j:当前已经匹配成功的,下一次要匹j + 1
    while (str[i]) {
        while (j != -1 && str[i] != pattern[j + 1]) j = next[j];
        if (str[i] == pattern[j + 1]) {
            j += 1;
            i += 1;         // 可以放到条件语句外
        } else {
            i += 1;
        }
        if (pattern[j + 1] == 0) return i - strlen(pattern); // 找到了模式串在母串的位置
    }
    return -1;
}

int main() {
    char str[100], pattern[100];

    while (scanf("%s%s", str, pattern) != EOF) {
        TEST(KMP, str, pattern);
        printf("%d\n", KMP(str, pattern));
    }

    return 0;
}
