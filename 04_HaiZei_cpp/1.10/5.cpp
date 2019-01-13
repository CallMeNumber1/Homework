/*************************************************************************
	> File Name: 5.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月10日 星期四 20时49分11秒
 ************************************************************************/

#include <iostream>
#include <string>

using namespace std;

class A {
    private:
        string name;
        int age;
    public:
    void print() {
        cout << name << " " << age << endl;
    }
};
class B : public A {};
class C : public A {};
class D : public B, public C {};

int main() {
    D d;
    B *pb = &d;
    C *pc = &d;
    void *pbb = pb;
    void *pcc = pc;
    if (pbb == pcc) {
        cout << "pointer equals" << endl;
    } else {
        cout << "not equal" << endl;
    }
    cout << "B:" << pb << "" << pbb << endl;
    cout << "C:" << pc << "" << pcc << endl;
    cout << &d << endl; // 地址与pc地址相同
    d.B::print();
    return 0;
}
