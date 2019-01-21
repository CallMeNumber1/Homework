/*************************************************************************
> File Name: const.cpp
> Author: ChongH
> Mail: 304451676@qq.com
> Created Time: 2019年01月21日 星期一 18时22分29秒
************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int main () {
    const Test t;
    Test &t1 = t;
    Test t2;
    const Test &t3 = t2;
    const Test &t4 = t;

}
