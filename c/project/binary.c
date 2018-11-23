/*************************************************************************
	> File Name: binary.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月08日 星期一 23时07分03秒
 ************************************************************************/

#include <stdio.h>
#include "binary.h"
double binary(double x) {
    double head = -1000, tail = 1000, mid;
    while (tail - head > EPS) {
        mid = (tail + head) / 2.0;
        if (mid * mid < x) head = mid;
        else tail = mid;
    }
    return head;
}

