/*************************************************************************
	> File Name: head.h
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月10日 星期四 20时25分27秒
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H
typedef void demo;
typedef void derived;
demo* demo_init(int i,  int j);
int getI(demo *pthis);
int getJ(demo *pthis);
int demo_add(demo *pthis, int value);
void demo_free(demo *pthis);

derived *derived_init(int i, int j, int k);
int getK(derived *pthis);
int derived_add(derived *pthis, int value);
void derived_free(derived *pthis);
#endif
