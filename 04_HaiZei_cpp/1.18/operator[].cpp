/*************************************************************************
	> File Name: operator[].cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 19时38分18秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class Test {
    private:
        int a[10];
    public:
    // 因为可以被赋值，因此返回引用
    int &operator[](int index) {
        return a[index];
    }
    int &operator[](const string &s) {
        if (s == "1st") return a[0];
        else if (s == "2th") return a[1];
        else if (s == "3th") return a[2];
        else if (s == "4th") return a[3];
        else if (s == "5th") return a[4];
        return a[0];
    }
};



int main() {
    int a[10] = {0, 1, 2};
    cout << 2[a] << endl;

    Test t;
    for (int i = 0; i < 5; i++) {
        t[i] = i + 1;
    }
    cout << t["1st"] << endl;
    cout << t["2nd"] << endl;
    cout << t["3th"] << endl;
    cout << t["4th"] << endl;
    cout << t["5th"] << endl;
    
    return 0;
}
