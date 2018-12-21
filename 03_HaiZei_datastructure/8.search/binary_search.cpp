/*************************************************************************
	> File Name: binary_search.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月06日 星期二 19时27分05秒
 ************************************************************************/

#include<iostream>
#include <stdio.h>
using namespace std;
#define P(func) { \
    printf("%s = %d\n", #func, func); \
}

// 普通二分
// 1 2 3 4 5 6
int binary_search1(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] > x) tail = mid - 1;
        else head = mid + 1;
    }
    return -1;
}

// 二分特殊情况1
//111111000000
int binary_search2(int *num, int n) {
    int head = - 1, tail = n - 1, mid;
    // 因为是要找到位置,而非元素
    while (head < tail) {
        // 加1后再除2, 这样在最后剩两个数时取得较后面的数,避免死循环
        mid = (head + tail + 1) >> 1;
        //printf("head:%d, tail:%d, mid:%d\n", head, tail, mid);
        // head变为mid而非mid + 1,以防错过答案
        if (num[mid] == 1) head = mid;
        else tail = mid - 1;
    }
    return head;
}

// 二分特殊情况2
//000000111111
int binary_search3(int *num, int n) {
    int head = 0, tail = n, mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == 1) tail = mid;
        else head = mid + 1;
    }
    return head == n ? -1 : head;
}

int main() {
    int arr1[10] = {1, 3, 5, 7, 11, 13, 17, 23, 27, 29};
    int arr2[10] = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0};
    int arr3[10] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
    P(binary_search1(arr1, 10, 11));
    P(binary_search2(arr2, 10));
    P(binary_search3(arr3, 10));
    return 0;
}
