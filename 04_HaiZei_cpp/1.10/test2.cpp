/*************************************************************************
	> File Name: test2.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月10日 星期四 18时19分55秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Parent {
    protected:
        int i;
    public:
    Parent(int v = 0) {
        i = v;
    }
    Parent() {
        cout << "Parent()" << endl;
    }
};
class Child : public Parent {
    public:
    Child() : Parent(5) {
        cout << "Child()" << endl;
    }
    int getI() {
        return i;
    }
};

class A {
    public:
    A() {
       cout << "A()" << endl; 
    }   
};
class B  : public A {
    public:
    B() {
        cout << "B()" << endl;
    }

};
class C {
    public:
    C() {
        cout << "C()" << endl;
    }
};
class D : public C {
    private:
        B b;
    public:
    D() {
        cout << "D()" << endl;
    }
};

int main() {
    Child c;
    cout << c.getI() << endl;
    
    D d;
    return 0;
}
