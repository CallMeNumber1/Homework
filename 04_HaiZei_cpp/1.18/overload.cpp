/*************************************************************************
	> File Name: overload.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 09时08分06秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

void add(int a, int b) {
    cout << "void add(int a, int b)" << endl;
    cout << a + b << endl;
    return ;
}
void add(int a) {
    cout << "void add(int)" << endl;
}

template <typename T>
void add(T a, T b) {
    cout << "void add(T a, T b)" << endl;
    cout << a + b << endl;
    return ;
}
void add(...) {
    cout << "void add(...)" << endl;
    return ;
}



int main() {
    add(1, 3);
    add<>(1, 3);
    add(2.4, 3.6);
    add(3);
    return 0;
}
