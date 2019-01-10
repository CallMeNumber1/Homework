#include <iostream>

using namespace std;
class Value {
    private:
        int i;
    public:
        Value(int v) : i(v) {
            cout << "value()" << i << endl;
        }
};
class Test {
    private:
        Value v1;
        Value v2;
    public:
        Test() : v1(1), v2(2) {
            cout << "hello" << endl;
        }
        ~Test() {
            cout << "bye" << endl;
        }
};
class Test1 {
    private:
        int i;
    public:
        Test1(int v) : i(v) {
            cout << "hello" << endl;
        }
        ~Test1() {
            cout << "bye" << endl;
        }
        int getI() {
            return i;
        }
};
class A {
    public:
        A() {
            cout << "construct A " << endl;  
        }
        ~A() {
            cout << "destruct A" << endl;
        }
};
class B {
    private:
        A a;
    public:
        B() {
            cout << "construct B " << endl;  
        }
        ~B() {
            cout << "destruct B" << endl;
        }
};
int main(){
    Test t;                 // 栈上空间
    Test *p = new Test;     // 堆上空间
    delete p;

    cout << "sequence test " << endl;
    B b;
    return 0;
}
