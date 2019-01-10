#include <iostream>
#include <stdio.h>
using namespace std;

int add() {
    return 1;
}
int add(int a, int b) {
    return a + b;
}
int add(int a, int b, int c) {
    return a + b + c;
}
int (*p1)(int, int);
int (*p2)();
int main(){
   printf("%p %p %p\n", add(), add(1, 2), add(1, 2, 3));
   p1 = add;
   p2 = add;
   printf("%p %p\n", p1, p2);
   return 0;
}
