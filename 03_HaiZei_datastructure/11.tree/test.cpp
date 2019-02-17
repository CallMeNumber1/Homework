/*************************************************************************
	> File Name: test.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年02月17日 星期日 19时34分47秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;
class A {
public:
    A(int x) : x(x) {}
    bool operator<(const A &obj) const {
        return this->x < obj.x;
    }
    A &operator<<(int &x) {
        x += 1;
        return *this;
    }
    A &operator>>(int &x) {
        x -= 1;
        return *this;
    }
    int x;
};

ostream &operator<<(ostream &out, const A &obj) {
    out << obj.x;
    return out;
}

typedef pair<int, int> PII;
int main() {
    A obj(0);
    int a = 1, b = 2, c = 3, d = 4;
    obj << a >> b >> c << d;
    cout << a << b << c << d;

    map<A, int> arr;
    arr[A(4)] = 5;

    for (auto x : arr) {
        // 还要重载这个cout.operator<<(const A &);
        cout << x.first << " " << x.second << endl;
    }
    set<PII> s;
    int op, val, cnt = 0;
    while (cin >> op >> val) {
        switch (op) {
            case 1: s.insert(PII(val, cnt++)); break;
            case 2: 
                cout << (*s.begin()).first << " " << (*s.begin()).second << endl; 
                s.erase(s.begin());
                break;
        }
    }

    return 0;
}
