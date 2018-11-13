/*************************************************************************
	> File Name: 2.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月08日 星期四 14时54分00秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int binary_search(int *num, int n) {
    int head = -1, tail = n - 1;
    while (head < tail) {
        int mid = (head + tail + 1) >> 1;
        if (num[mid] <= 0) {
            tail = mid - 1;
        } else {
            head = mid;
        }
    }
    return head;
}
int main() {
    int n;
    scanf("%d", &n);
    int *num = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", num + i);
    }
    return 0;
}

