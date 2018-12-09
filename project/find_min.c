/*************************************************************************
	> File Name: find_min.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年12月09日 星期日 20时02分38秒
 ************************************************************************/

#include <stdio.h>
#include "find_min.h"
// 传出的是最小的下标，而非最小值!!!!!!
int find_min(int n, int *arr) {
    int min = 100, ind = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
            ind = i;
        } 
    }
    return ind;
}

