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

int Sunday(char *str, char *pattern) {
    #define BASE 128
    int ind[BASE] = {0};        // 每一种字符在原字符串出现位置
    int len = strlen(pattern), max_len = strlen(str);
    for (int i = 0; i < BASE; i++) {
        ind[i] = len + 1;
    }
    for (int i = 0; i < len; i++) {
        ind[pattern[i]] = len - i; // 每一个字符最后出现的位置
    }
    for (int i = 0; i < max_len;) {
        int flag = 1;
        for (int j = 0; j < len; j++) {
            if (str[i + j] == pattern[j]) continue;
            i += ind[str[i + len]];     // 加上 黄金对齐点位的字符出现在倒数第几位
            flag = 0;
            break;
        }
        if (flag) return i;
    }
    return -1;
}

int ShiftAnd(char *str, char *pattern) {
    #define BASE 128
    // 每个字符的编码
    int code[BASE] = {0}, len = 0;
    for (len = 0; pattern[len]; len++) {
        code[pattern[len]] |= 1 << len;     // 将相关字符编码的相应位置置1
    }
    int p = 0;          // 初始状态p
    for (int i = 0; str[i]; i++)  {
        // p的状态转移
        p = (p << 1 | 1) & code[str[i]];
        // 如果成立, 则已经匹配成功
        if (p & (1 << (len - 1))) return i - len + 1;
    }
    return -1;
}

int ShiftAndAny(char *str, char *pattern) {
    #define BASE 128
    #define MAX 100
    char code[BASE][MAX] = {0}, len = 0;
    for (int i = 0; i < BASE; i++) {
        for (int j = 0; j < MAX - 1; j++) {
            code[i][j] = '0';
        }
    }
    for (len = 0; pattern[len]; len++) {
        code[pattern[len]][len] = '1';
        //printf("char:%c, code: %s\n",pattern[len], code[pattern[len]]); 
    }
   // printf("len = %d\n", len);
    char p[MAX] = {0};
    for (int i = 0; i < len; i++) p[i] = '0';
    for (int i = 0; str[i]; i++) {
        int temp = len;
        //printf("pre p:%s\n", p);
        for (int j = temp; j >= 0; j--) p[j + 1] = p[j];
        p[0] = '1';
        temp++; // 模拟二进制左移运算
        //printf("post p:%s\n", p);
        for (int k = 0; k < temp; k++) {
            if (p[k] == '1' && code[str[i]][k] == '1') {
                p[k] = '1';
            } else {
                p[k] = '0';
            }
        }
        if (p[len - 1] == '1') return i - len + 1;   
    }
    return -1;
    #undef BASE
    #undef MAX
}


int main() {
    char str[100], pattern[100];

    while (scanf("%s%s", str, pattern) != EOF) {
        TEST(KMP, str, pattern);
        TEST(Sunday, str, pattern);
        TEST(ShiftAnd, str, pattern);
        TEST(ShiftAndAny, str, pattern);
    }

    return 0;
}
