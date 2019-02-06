/*************************************************************************
	> File Name: manacher.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月17日 星期四 16时03分34秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
char s[MAX + 5] = {0};
char s_new[MAX * 2 + 5] = {0};
int p[2000];                // p[i]记录以i为中心的最长回文串

int min(int a, int b) {
    return a < b ? a : b;
}
int max(int a, int b) {
    return a > b ? a : b;
}
int init() {
    s_new[0] = '$';
    s_new[1] = '#';
    int j = 2;
    for (int i = 0; s[i]; i++) {
        s_new[j++] = s[i];
        s_new[j++] = '#';
    }
    s_new[j] = '\0';
    return j;               // 返回s_new的长度
}
int Manacher() {
    int len = init();       // 新字符串长度
    int max_len = -1;       // 最长回文长度
    int id, mx = 0;
    for (int i = 1; i < len; i++) {
        if (i < mx) {
            p[i] = min(p[2 * id - 1], mx - i);
        } else p[i] = 1;
        // 不需要边界判断，因为左有'$',右有'\0'
        while (s_new[i - p[i]] == s_new[i + p[i]]) p[i]++;
        // 每走一步i，都要和mx比较
        // 我们希望mx尽可能走的远，这样才有机会执行if(i < mx)这句代码
        if (i + p[i] > mx) {
            id = i;
            mx = i + p[i];
        }
        max_len = max(max_len, p[i] - 1);
    }
    return max_len;
}


int main() {
    scanf("%s", s);
    printf("%d\n", Manacher());
    
    return 0;
}


