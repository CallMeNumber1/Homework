/*************************************************************************
	> File Name: scan.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月13日 星期四 19时16分04秒
 ************************************************************************/
// 可以读入空格的scanf()
#include <stdio.h>

int main() {
    int n;
    char str[100];
    scanf("%[^\n]s", str);
    n = printf("%s", str);
    printf(" has %d digits\n", n);
    return 0;
}
