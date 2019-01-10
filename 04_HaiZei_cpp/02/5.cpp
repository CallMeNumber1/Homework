#include <iostream>

using namespace std;

int add(int a, int b);
int main() {
    int a = 5, b = 4;
    cout << add() << endl;

    return 0;
}
int add(int a = 1, int b = 1) {
    return a + b;
}