/*************************************************************************
	> File Name: binary.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月23日 星期日 10时41分11秒
 ************************************************************************/

#include <stdio.h>
// 数组
int binary(int *arr, int x, int n) {
    int head = 0, tail = n - 1;
    while (head <= tail) {
        int mid = (head + tail) >> 1;
        if (arr[mid] == x) return mid;
        else if (arr[mid] < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}
// 函数
int binary1(int (*arr)(int), int x, int n) {
    int head = 0, tail = n - 1;
    while (head <= tail) {
        int mid = (head + tail) >> 1;
        if (arr(mid) == x) return mid;
        else if (arr(mid) < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    printf("%d\n", binary(arr, 3, 5));
    return 0;
}
