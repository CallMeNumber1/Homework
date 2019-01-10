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
        Value v1;
        Value v2;
        Value v3;
    public:
        Test();
};
Test::Test(): v1(1), v2(2), v3(3) {
    cout << "Test:" << endl;
}

int main(){
   Test t;
   
   return 0;
}
