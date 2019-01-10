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
    int add() {
        return i + 1;
    }
    int add(int a, int b, int c) {
        return i + a + b + c;
    }
    int get() {
        cout << "A::i = " << i << endl;
        return i;
    }
    void say() {
        cout << "hello i'm a" << endl;
    } 
};

class B : public A {
    public:
        int i;
    public:
    B(int v) : A(0) {
        i = v;
    }
    int add(int a) {
        return i + a;
    }
    /*
    int add(int a, int b) {
        return i + a + b;
    }
    int get() {
        cout << "B::i = " << endl;
        return i;
    }
    */
    void say() {
        cout << "hello i'm b" << endl;
    }
};

void how_to_say(A *p) {
    p->say();
    return ;
}
int main() {
    B b(3);
    A a(0);
    cout << b.i << endl;
    cout << b.A::i << endl;
    cout << "sizeof(a):" << sizeof(a) << endl;
    cout << "sizeof(b):" << sizeof(b) << endl;

    cout << b.A::add() << endl; // 1
    cout << b.A::add(1, 2, 3) << endl; // 6
    cout << b.get() << endl;
    how_to_say(&a);
    how_to_say(&b);
    return 0;
}
