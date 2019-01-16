/************************************************************************
	> File Name: 4.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月16日 星期三 15时19分26秒
 ************************************************************************/

// 单继承+多接口

#include <iostream>
#include <string>
using namespace std;
class Base {
protected:
    int a;
public:
    Base(int v1) {
        a = v1;
    }
    int get() {
        return a;
    }
    bool equal(Base *p) {
        return this == p;
    }
};
class Interface1 {
    public:
    virtual void add(int i) = 0;
    virtual void sub(int i) = 0;
};
class Interface2 {
    public:
    virtual void mul(int i) = 0;
    virtual void div(int i) = 0;
};

class Derived : public Base, public Interface1, public Interface2 {
public:
    Derived(int i) : Base(i) {

    }
    void add(int i) {
        a += i;
    }
    void sub(int i) {
        a -= i;
    }
    void mul(int i) {
        a *= i;
    }
    void div(int i) {
        if (i != 0) a /= i;
    }
};

int main() {
    Derived d(10);
    Derived *p = &d;
    Interface1 *p1 = &d;
    Interface2 *p2 = &d;
    if (p->equal(dynamic_cast<Base*>(p1)) && p->equal(dynamic_cast<Base*>(p2))) {
        p1->add(10);    //20
        p1->sub(5);     //15
        p2->mul(10);    //150
        p2->div(10);    //15
    }
    cout << p->get() << endl;
    return 0;
}
