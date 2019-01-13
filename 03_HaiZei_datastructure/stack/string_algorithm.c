#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TEST(func, a, b) { \
    printf("%s(%s, %s) = %d\n", #func, a, b, func(a, b)); \
} \



//　第一次出现位置　没有则－１
int  Bruteforce(char *str, char *pattern) {
    for (int i = 0; str[i]; i++) {
        int flag = 1;
        for (int j = 0; pattern[j]; j++) {
            if (str[i + j] == pattern[j]) continue;
            flag  = 0;
            break;
        }
        if (flag) return i;
    }
    return -1;
}

int KMP(char *str, char *pattern) {
    int *next=  (int *)malloc(sizeof(int) * strlen(pattern));
    next[0] = -1;
    for (int i = 1; pattern[i]; i++) {
        int j = next[i - 1];
        while (j != -1 && pattern[j + 1] != pattern[i]) j = next[j];
        if (pattern[j + 1] == pattern[i]) next[i] = j + 1;
        else next[i] = -1;
    }   
    int i = 0, j = -1;
    while (str[i]) {
        while (j != -1 && str[i] != pattern[j + 1]) j = next[j];
        if (str[i] == pattern[j + 1]) {
            j += 1;
        }                   // 当前位没有匹配上
        i += 1;
        if (pattern[j + 1] == 0)  return i - strlen(pattern);
    }
    return -1;
}

int Sunday(char *str, char *pattern) {
    #define BASE 128
    // 每一个字符出现的位置
    int ind[BASE] = {0};
    int len = strlen(pattern), max_len = strlen(str);
    for (int i = 0; i < BASE; i++) {
        ind[i] = len + 1;
    }
    for (int i = 0; i < len; i++) {
        ind[pattern[i]] = len - i;
    }

    for (int i = 0; i < max_len;) {
        int flag = 1;
        for (int j = 0; j < len; j++) {
            if (str[i + j] == pattern[j]) continue;
            i += ind[str[i + len]];     
            flag = 0;
            break;
        }
        if (flag) return i;
    }
    return -1;
    #undef BASE
}

// FIXME:当字符串超过一定长度后就出错(因为整型范围问题)
int ShiftAnd(char *str, char *pattern) {
    // TODO:改成支持任意长度字符的算法
    // TODO:深刻理解数据结构=数据定义+数据操作
    #define BASE 128        // 字符种类
    int code[BASE] = {0}, len = 0;
    for (len = 0; pattern[len]; len++) {
        code[pattern[len]] |= (1 << len);       // 相关相应字符编码置1
    }
    int p = 0;
    for (int i = 0; str[i]; i++) {
        p = (p << 1 | 1) & code[str[i]];
        if (p & (1 << (len - 1))) return i - len + 1;
    }
    return -1;
    #undef BASE
}

int main(){
    char str[100], pattern[30];
    while (scanf("%s%s", str, pattern) != EOF) {
        TEST(Bruteforce, str, pattern);
        TEST(KMP, str, pattern);
        TEST(Sunday, str, pattern);
        TEST(ShiftAnd, str, pattern);
    }
    return 0;
}
