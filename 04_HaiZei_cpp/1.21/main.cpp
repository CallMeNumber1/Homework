/*************************************************************************
	> File Name: main.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月21日 星期一 19时17分25秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;
int func(int i) {
    cout << "func::i = " << i << endl;
}

class Test {
    private:
        int i;
    public:
    Test(int v = 0) {
        i = v;
    }
    // const的对象只能调用const方法，因此声明const``
    int getI() const{
        return this->i;
    }
};

bool operator&&(const Test &obj1, const Test &obj2) {
    return (obj1.getI() && obj2.getI());
}
bool operator||(const Test &obj1, const Test &obj2) {
    return (obj1.getI() || obj2.getI());
}
Test func1(Test obj) {
    cout << "Test::obj.i = " << obj.getI() << endl;
    return obj;
}
int main() {
// 模拟逻辑运算的最短路原则
    if (func(0) && func(1)) {
        cout << "true" << endl;
    } else {
        cout << "true" << endl;
    }

    if (func(1) || func(0)) {
        cout << "true" << endl;
    } else {
        cout << "true" << endl;
    }
    cout << "Test operator : " << endl;
    Test t1(1), t2(2);
    if (func1(t1) && func1(t2)) { 
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    if (func1(t2) || func1(t1)) {//operator||(func1(t1),func1(t2))
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}
