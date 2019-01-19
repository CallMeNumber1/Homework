/*************************************************************************
	> File Name: calc.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月13日 星期日 15时19分16秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
using namespace std;


int ans = 0;
// 以某点作为中心的扩展
void expand(char *str, int i, int j, int n) {
    // 合法的情况
    while (i >= 0 && j < n && str[i] == str[j]) {
        char c = str[j + 1];
        str[j + 1] = 0;
        //printf("%s\n", str + i);
        int temp = strlen(str + i);
        if (temp > ans) ans = temp;
        str[j + 1] = c;
        i--; j++;
    }
    return ;
}
int main() {

    char str[1000];
    scanf("%s", str);
    int len = strlen(str);
    for (int i = 0; str[i]; i++) {
        // 向两边扩展
        //printf("%c\n", str[i]);
        // 分别处理回文串为奇数和偶数的情况
        expand(str, i, i, len); 
        expand(str, i, i + 1, len);
    }
    printf("%d\n", ans);
    /*
    for (int i = 0; str[i]; i++) {
        for (int j = i; str[j]; j++) {
            if (is_valid(str, i, j)) {
                char c = str[j + 1];
                str[j + 1] = 0;
                printf("%d %d(%s)\n", i, j, str + i);
                str[j + 1] = c;
            }   
        }
    }
    */
}
