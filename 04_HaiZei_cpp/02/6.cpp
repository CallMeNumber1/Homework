#include <iostream>

using namespace std;
void g(int = 0, int = 0, int = 0) {
    cout << "hello g" << endl;
}
int main() {
    g();
    g(1, 2, 3);
    return 0;
}