/*************************************************************************
	> File Name: multi_inherit.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月16日 星期三 14时53分08秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class BaseA {
    public:
    virtual void funcA() {
        cout << "BaseA::funcA" << endl;
    }
    virtual void func() {
        cout << "just a test" << endl;
    }
};
class BaseB {
    public:
    virtual void funcB() {
        cout << "BaseB::funcB" << endl;
    }
};
class Derived: public BaseA, public BaseB {
};

int main() {
    cout << sizeof(Derived) << endl;
    Derived d;
    BaseA *p1 = &d;
    BaseB *p2 = &d;
    p1->funcA();
    p2->funcB();
    // 强转失败情况
    BaseB *pb = (BaseB *)p1;
    pb->funcB();
    //
    BaseB *pbb = dynamic_cast<BaseB*>(p1);
    pbb->funcB();
    return 0;
}
