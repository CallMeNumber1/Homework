/*************************************************************************
	> File Name: revTest.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月10日 星期四 17时12分33秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Test {
    private:
        int i;
    public:
    Test(int v) {
        i = v;
        cout << "Test(int i) : i = " << i << endl; 
    }
    Test() {
        i = 0;
        cout << "Test() : i = " << i << endl;
    }
    Test(const Test &t) {
        i = t.i;                    //为何可以直接用t.i
        cout <<  "Test(copy) : i = " << i << endl;
    }
    void printI() {
        cout << "i = " << i << endl;
    }
};
void func1(Test t) {
    return ;
}
Test func2() {
    return Test(100);
}

int main() {
    Test t = Test(100);
    t.printI();
    func1(t);
    Test t1 = func2();
    t1.printI();
    return 0;
}
