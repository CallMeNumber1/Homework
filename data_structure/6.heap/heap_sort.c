/*************************************************************************
	> File Name: heap_sort.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月30日 星期二 20时27分40秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) { \
    __typeof(a) __temp = a; a = b; b = __temp; \
}

void head_sort(int *arr, int n) {
    // 改变数组的映射 p[1]即a[0]
    int *p = arr - 1;
    // 建堆
    for (int i = 2; i <= n; i++) {
        int ind = i;
        while (ind > 1) {
            if (p[ind] <= p[ind >> 1]) break;
            swap(p[ind], p[ind >> 1]);
            ind >>= 1;
        }
    }
    // 弹出操作
    for (int i = n; i > 1; i--) {
        swap(p[i], p[1]);
        int ind = 1;
        // 为什么<=i-1?因为最后一位相当于是删去,在排序情境中是
        // 已经确立了最后的位置,不必参与处理了
        while ((ind << 1) <= i - 1) {
            int temp = ind;
            if (p[temp] < p[ind << 1]) temp = ind << 1;
            if ((ind << 1 | 1) <= i - 1 && p[temp] < p[ind << 1 | 1]) temp = ind << 1 | 1;
            if (temp == ind) break;
            swap(p[temp], p[ind]);
            ind = temp;
        }
    }
    return ;
}

void output(int *num, int n) {
    printf("Arr = [");
    for (int i = 0; i < n; i++) {
        printf(" %d", num[i]);
        i == n - 1 || printf(",");
    }
    printf("]\n");
    return ;
}

int main() {
    #define MAX_N 20
    int arr[MAX_N];
    srand(time(0));
    for (int i = 0; i < MAX_N; i++) {
        arr[i] = rand() % 100;
    }
    output(arr, MAX_N);
    head_sort(arr, MAX_N);
    output(arr, MAX_N);
    return 0;
}
