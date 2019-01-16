/*************************************************************************
	> File Name: template2.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月16日 星期三 16时46分18秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;
template <typename T1, typename T2, typename T3>
T1 add(T2 a, T3 b) {
    return static_cast<T1>(a + b);
}


int main() {
    int r1 = add<int>(0.5, 0.3);
    int r2 = add<int, float>(0.3, 0.6);
    int r3 = add<int, float, float>(0.5, 0.5);
    cout << r1 << endl;
    cout << r2 << endl;
    cout << r3 << endl;
    return 0;
}
