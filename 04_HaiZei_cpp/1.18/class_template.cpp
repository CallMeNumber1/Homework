/*************************************************************************
	> File Name: class_template.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 09时36分52秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;
template <typename T>
class Test {
    private:
        T a;
    public:
    Test(T v) {
        a = v;
    }
    T get() {
        return a;
    }
    T add (T b) {
        T ret = a + b;
        return ret;
    }
    T sub(T b) {
        return a - b;
    }
    friend string operator-(const string &s1, const string &s2);
};

string operator-(const string &s1, const string &s2) {
    return "hello world";
}
int main() {
    Test<int> t(0);
    cout << t.get() << endl;
    cout << t.add(10) << endl;
    string s1 = "wrf";
    string s2 = "haizeix.om";
    Test<string> t1(s1);

    cout << t1.get() << endl;
    cout << t1.add(" " + s2) << endl;
    cout << t1.sub(" ") << endl;
    return 0;
}
