/*************************************************************************
	> File Name: exception4.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 15时10分07秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class Base {
    

};

class Exception : public Base {
    private:
        int i;
        string info;
    public:
    Exception(int v1, string s1) {
        i = v1;
        info = s1;
    }
    void what() {
        cout << "exception id is " << i << endl;
        cout << "exception info is " << info << endl;
    }
};



void func(int i) {
    if (i < 10) {
        throw -1;
    } else if (i < 20) {
        throw -2;
    } else if (i < 30) {
        throw -3;
    }
    return ;
}

void myfunc(int i) {
    try {
        func(i);
    } catch (int i) {
        switch (i) {
            case -1: {
                throw Exception(-1, "Rntime Error");
                throw "Run Error";  // 将一个类型异常转化为另一个
            } break;
            case -2: {
                throw Exception(-1, "Rntime Error");
                throw "Parameter Error";
            } break;
            case -3: {
                throw Exception(-1, "Rntime Error");
                throw "Segement Fault";              
            } break;
        }
    }
    return ;
}

int main() {
    
    int i;
    cin >> i;
    try {
        myfunc(i);
    } catch (Base &b) {
        cout << "Base exception" << endl;
    } catch (Exception &e) {
        e.what();
    } catch (Base &b) {
        cout << "Base exception" << endl;
    } catch (...) {
        cout << "Other Exception" << endl;
    }
    cout << "done" << endl;
    return 0;
}

