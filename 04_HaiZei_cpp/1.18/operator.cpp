/*************************************************************************
	> File Name: operator.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 18时25分29秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;


int main() {
    int a, b = 1, c = 0;
    (a = b) = c;
    // (a=b)形成了一个a的引用,再把c赋给a
    cout << a << b << c;        // 0 1 0
    return 0;
}
