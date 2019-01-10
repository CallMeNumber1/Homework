/*************************************************************************
	> File Name: 4.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月10日 星期四 20时01分33秒
 ************************************************************************/

#include<iostream>
using namespace std;
class Test {
    private:
        int i;
        int j;
    public:
    Test(int v1 = 0, int v2 = 0) {
        i = v1;
        j = v2;
    }
    int getI() {
        return i;
    }
    int getJ() {
        return j;
    }
    int add(int value) {
        return i + j + value;
    }
    ~Test() {}
};
class A {
    private:
        int a;
        int b;
        char c;
        double d;
    public:
    void print() {
        cout << "a = " << a << endl;
    }   
};

struct B {
    int a;
    int b;
    char c;
    double d;
};


int main() {
    Test t(1, 3);
    cout << t.getI() << " " << t.getJ() << endl;
    cout << t.add(10) << endl;
    
    A a;
    B b;
    cout << sizeof(a) << " " << sizeof(b) <<  endl;
    a.print();
    B *p = reinterpret_cast<B *>(&a);
    p->a = 100;
    a.print();
    p->a = 1234;
    a.print();
    return 0;
}
