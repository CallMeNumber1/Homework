
#include <iostream>

using namespace std;


void swap(int *a, int *b) {
    int *temp = a;
    *a = *b;
    *b = *temp;
    return ;
}

void swap1(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int& f() {
    int a = 100;
    int &b = a;
    return b;
}

int main() {
    int a = 1, b = 3;
    swap(&a, &b);
    swap1(a, b);
    cout << a << " " << b << endl;
    int c = 2;    
    c = f();
    cout<<c<<endl;
    return 0;
}
