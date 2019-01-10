/*************************************************************************
	> File Name: test3.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月10日 星期四 19时02分54秒
 ************************************************************************/

#include<iostream>
using namespace std;

class A {
    public:
       int i;
    public:
    A(int v = 0) {
        i = v;
    }
    int get() {
        return i;
    }
};

class B : public A {
    public:
        int i;
    public:
    B(int v) : A(0) {
        i = v;
    }
    int get() {
        return i;
    }
};

int main() {
    B b(3);
    A a(0);
    cout << b.i << endl;
    cout << "sizeof(a):" << sizeof(a) << endl;
    cout << "sizeof(b):" << sizeof(b) << endl;
    return 0;
}
