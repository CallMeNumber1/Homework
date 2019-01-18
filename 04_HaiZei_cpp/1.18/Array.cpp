/*************************************************************************
	> File Name: Array.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 19时07分27秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;


// 将int换成T即可做成数组模板
class Array {
    private:
        int m_len;
        int *data;
    public:
    Array (int len = 0) {
        data = new int[len];
        for (int i = 0; i < len; i++) {
            data[i] = 0;
        }
        m_len = len;
    }
    // 重载了=号运算符
    Array& operator=(const Array &obj) {
        if (this != &obj) {         // 排除自赋值
            int *p = new int[obj.m_len];
            this->m_len = obj.m_len;
            if (p) {
                for (int i = 0; i < obj.m_len; i++) {
                    p[i] = obj.data[i];
                }
                m_len = obj.m_len;
                delete[] data;
                data = p;
            }
        }
        return *this;
    }
    // 增加了[]运算符重载,则set、get函数可以略去了
    int& operator[](int index) {
        if (index < m_len && index >= 0) {
            return data[index];
        } else {
            // TODO:异常处理
        }
    }
    void set(int index, int value) {
        if (index >= 0 && index < m_len) {
            data[index] = value;
        }
    }
    int get(int index) {
        if (index >= 0 && index < m_len) {
            return data[index];
        }
    }
};
int main() {
    Array a1(5);
    for (int i = 0; i < 5; i++) {
        a1[i] = i + 1;
    }
    for (int i = 0; i < 5; i++) {
        cout << a1[i] << " ";
    }
    cout << endl;
    
    Array a2(10);
    for (int i = 0; i < 10; i++) {
        a2.set(i, i + 1);    
    }
    a1 = a2;
    for (int i = 0; i < 10; i++) {
        cout << a1.get(i) << " ";
    }
    cout << endl;
    return 0;
}
