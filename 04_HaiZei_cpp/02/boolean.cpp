#include <iostream>

using namespace std;
int main() {

    int a = 5;
    bool b = false;
    cout << sizeof(b) << endl;
    cout << a << b <<endl; // 5 0
    b++;
    cout << a << b <<endl; // 5 1
    a = b + a;
    cout << a << b <<endl; // 6 1
    
    return 0;
}