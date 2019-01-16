/*************************************************************************
	> File Name: template.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月16日 星期三 15时57分45秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;
#define swap(t, a, b) { \
    t (temp) = (a); \
    (a) = (b); \
    (b) = (temp); \
}
void my_swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    return ;
}
void my_swap(string &s1, string &s2) {
    string temp = s1;   // 调用拷贝构造
    s1 = s2;            // 调用重载的等号
    s2 = temp;
    return ;
}

template <typename T>
void my_swap1(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

class Test {
public: 
    Test(const Test &t) {

    }
public:
    Test() {

    }
};
template <typename T>
void my_sort(T *a, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            if (a[i] > a[j]) {
                my_swap1(a[i], a[j]);
            }
        } 
    }
    return ;
}

// 自动类型推导
template <typename T>
void print(T *a, int len) {
    for (int i = 0; i < len; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return ;
}

int main() {
    int a = 10, b = 20;
    string s1 = "wrf", s2 = "cxh";
    swap(int, a, b);
    cout << a << " " << b << endl;
    my_swap(s1, s2);
    cout << s1 << " " << s2 <<endl;
    Test t1, t2;
    my_swap1(t1, t2);

    int aa[5] = {3, 2, 1, 4, 6};
    double bb[5] = {3.1, 4.2, 1.7, 4.3, 0.2};
    string s[5] = {"c", "python", "java", "cpp", "c#"};
    my_sort(aa, 5);
    //也可以显示指定
    //my_sort<int>(aa, 5);
    print(aa, 5);
    my_sort(s, 5);
    print<string>(s, 5);
    return 0;
}
