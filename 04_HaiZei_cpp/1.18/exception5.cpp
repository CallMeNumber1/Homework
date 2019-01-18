/*************************************************************************
	> File Name: exception5.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 15时54分05秒
 ************************************************************************/


// C++异常类的使用
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;


int main() {
    int n;
    int a[10] = {0};
    cin >> n;
    try {
        if (n < 10) {
            for (int i = 0; i < n; i++) {
                a[i] = i + 1;
            }
        } else {
            throw out_of_range("out of range");
        }
    } catch (out_of_range e) {
        cout << e.what() << endl;
    }
    cout << "done" << endl;
    return 0;
}
