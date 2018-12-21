/*************************************************************************
	> File Name: test04.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月18日 星期二 20时51分13秒
 ************************************************************************/
// 计算数字位数
// 若使用while循环,则当n=0时,cnt赋初值1,n不为0时,赋初值0
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int cnt = (n == 0);
    while (n) {
        n = n / 10;
        cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}
