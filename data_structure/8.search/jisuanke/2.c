/*************************************************************************
	> File Name: 2.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月08日 星期四 14时54分00秒
 ************************************************************************/

#include <stdio.h>
#define MAX 100005


int binary_search(int *num, int n, int key) {
    int head = -1, tail = n - 1;
    while (head < tail) {
        int mid = (head + tail + 1) >> 1;
        if (num[mid] > key) {
            tail = mid - 1;
        } else {
            head = mid;
        }
    }
    return head;
}
int main() {
    int n, m;
    int num[MAX], temp;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &temp);
        int ind = binary_search(num, n, temp);
        // 当找不到时,输出最小的,即下标为0
        if (ind == -1) ind = 0;
        printf("%d", num[ind]);
        i == m - 1 || printf(" ");
    }
    printf("\n");
    return 0;
    
}

