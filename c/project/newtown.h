/*************************************************************************
	> File Name: newton.h
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月08日 星期一 22时10分31秒
 ************************************************************************/

#ifndef _NEWTON_H
#define _NEWTON_H
#define EPS 1e-7
double f1(double, double);
double f1_prime(double);
double newtown(double, double (*f)(double, double), double (*f_prime)(double));
#endif
