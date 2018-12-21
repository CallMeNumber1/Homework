/*************************************************************************
	> File Name: newton.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月08日 星期一 22时09分36秒
 ************************************************************************/

#include <stdio.h>
#include <math.h>
#include "newtown.h"
#include "test.h"
double f1(double x, double n) {
    return x * x - n;
}
double f1_prime(double x) {
    return 2.0 * x;
}
double newtown(double n, double (*f)(double, double), double (*f_prime)(double) ) {
    double x = 1.0;
    while (fabs(f(x, n)) > EPS) {
        x -= f(x, n) / f_prime(x);
    }
    return x;
}

