/*************************************************************************
	> File Name: template1.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 11时35分19秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

template <int N>
void fun() {
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        sum += i;
    }
    cout << sum << endl;
    return ;
}
template <typename T, int N>
class Test {
    private:
        T a[N];
    public:
    Test() {
        for (int i = 0; i < N; i++) {
            a[i] = i + 1;
        }
    }
    void print() {
        for (int i = 0; i < N; i++) {
            cout << a[i] << " " << endl;
        }
    }   
};


// 要处理字符串的情况，要特化一下
template <int N>
class Test<string, N> {
    private:
        string a[N];
    public:
    Test() {
        for (int i = 0; i < N; i++) {
            a[i] = "wrf";
        }
    }
    void print() {
        for (int i = 0; i < N; i++) {
            cout << a[i] << endl;
        }      
    }
};

int main() {
    fun<10>();
    Test<int, 10> t;
    t.print();

    Test<string, 10> t2;
    t2.print();
    return 0;
}
