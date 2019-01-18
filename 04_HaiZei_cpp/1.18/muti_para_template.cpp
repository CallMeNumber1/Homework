/*************************************************************************
	> File Name: muti_para_template.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 10时41分01秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
class Test {
    public:
        void add(T1 a, T2 b) {
            cout << "void add(T1 a, T2 b)" << endl;
            cout << a + b << endl;
        }
};
// 部分特化
template <typename T>
class Test<T, T> {
    public: 
    void add(T a, T b) {
        cout << "void add(T a, T b)" << endl;
        cout << a + b << endl;
    }
    void print() {
        cout << "specialize" << endl;
    }
}; 
template <typename T>
class Test<T*, T*> {
    public:
    void add(T *a, T *b) {
        cout << "void add(T *a, T *b)" << endl;
        cout << *a + *b << endl;
    }
};
// 注意二义性问题
/*
template <typename T>
class Test<T, int> {
    public:
    void add(T a, int b) {
        cout << "void add(T a, int b)" << endl;
        cout << a + b << endl;
    }
};
*/
// 完全特化
template <>
class Test<void *, void *> {
    public:
    void add(void *a, void *b) {
        cout << "void add(void *a, void *b)" << endl;
        cout << "ERROR!" << endl;
    }
};



template <typename T>
bool equal(T a, T b) {
    cout << "bool equal(T, T)" << endl;
    return a == b;
}
// 函数模板的特化（只支持完全特化）
template <>
bool equal<double>(double a, double b) {
    cout << "bool equal<double>(double, double)" << endl;
    const double x = 1e-7;
    double ret = a - b;
    return ((ret > -x) && (ret < x));
}
int main() {
    cout << "---class_template---" << endl;
    Test<int, float> t1;
    t1.add(2, 4.3);
    Test<int, int> t2;
    t2.add(1, 2);
    int a = 1, b = 2;
    Test <int*, int *> t3;
    t3.add(&a, &b);
    Test<void *, void *> t4;
    t4.add(NULL, NULL);


    cout << "---func_template---" << endl;
    cout << equal(a, b) << endl;
    cout << equal(3.2, 3.2) << endl;
    return 0;
}
