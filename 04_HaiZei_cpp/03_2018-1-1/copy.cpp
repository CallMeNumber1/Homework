#include <iostream>

using namespace std;

class Test {
    private:
        int a;
        int *p;
    public:
        Test(int value) {
            a = value;
            p = new int(1);
            cout << "Test(int)" << a << endl;
        }
        Test(const Test &obj) {
            a = obj.a;
            p = new int;
            // FIXME:?? 此处是否为将指针分配给值??
            *p = *(obj.p);
        }
        int getA() {
            return a;
        }
        int *getP() {
            return &a;
        }
};

int main(){
   Test *a = new Test(1);
   Test t3(1); 
   Test t5 = t3;
   
   
   return 0;
}
