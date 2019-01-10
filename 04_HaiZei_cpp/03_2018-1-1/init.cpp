#include <iostream>

using namespace std;
class Value {
    private:
        int i;
    public:
        Value(int v) : i(v) {
            cout << "Value :: i = " << i << endl;
        }
};
class Test {
    private:
        const int i;
        int a;
        Value v1;
    public:
        Test(int v1, int v2);
        int getI() {
            return i;
        }
};
Test::Test(int v1, int v2) :  i(v1), a(v2), v1(1) {
    cout << "i = " << i << endl;
    cout << "a = " << a << endl;
}

int main(){
   Test t(10, 20);
   cout << "t.i = " << t.getI() << endl;
   
   return 0;
}
