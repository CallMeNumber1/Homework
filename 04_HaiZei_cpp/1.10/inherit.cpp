/*************************************************************************
	> File Name: inherit.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月10日 星期四 18时05分20秒
 ************************************************************************/

#include<iostream>
using namespace std;
class Parent {
    private:
        int a;
    public:
        int b;
    void set(int v1, int v2, int v3) {
        a = v1;
        b = v2;
        c = v3;
    }
    protected:
        int c;
};

class Child1 : public Parent {
    public:
    void print() {
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;
    }
};

class Child2 : private Parent {
    public:
    void print() {
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
        cout << "c = " << c << endl;
    }
};

class Child3 : protected Parent {
    public:
    void print() {

    } 
};

class Test : public Child3 {
    void set(int v) {
        b = v;
    }
};
int main() {
    Child2 c2;
    c2.b = 10;
    Child3 c3;
    c3.b = 100;
    return 0;
}
