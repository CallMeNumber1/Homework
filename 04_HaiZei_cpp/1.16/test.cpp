/*************************************************************************
	> File Name: test.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月16日 星期三 10时24分01秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class A {
    protected:
        int i, j;
    public:
    A(int v1, int v2) {
        i = v1;
        j = v2;
    }
    virtual void print() {
        cout << "hello" << endl;
    }
};

class B: public A {
    private:
        int k;
    public:
    B(int v1, int v2, int v3) : A(v1, v2) {
        k = v3;
    }
    void show() {
        cout <<  "i = " << i << endl;
        cout <<  "j = " << j << endl;
        cout <<  "k = " << k << endl;
    }
};

typedef struct C {
    void *ptr;
    int a;
    int b;
    int c;
} C;


int main() {
    B b(1, 2, 3);
    b.show();
    C *p = reinterpret_cast<C *>(&b);
    p->a = 10;
    p->b = 100;
    p->c = 1000;
    b.show();
    return 0;
}
