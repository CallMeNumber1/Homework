#include <stdio.h>

int main() {
    const int a = 5;
    int *p = (int *)&a;
    *p = 6;
    printf("%d %d\n", a, *p);
    return 0;
}