#include <iostream>

using namespace std;

int main() {
    int a = 1,  b = 2;
    (a > b ? a : b) = 3;
    cout << a << " " << b << endl;
    return 0;
}