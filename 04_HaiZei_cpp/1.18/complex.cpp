/*************************************************************************
	> File Name: complex.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 16时20分43秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class Complex {
    private:
        double real, imag;
    public:
    Complex(double v1 = 0, double v2 = 0) {
        real = v1;
        imag = v2;
    }
    double getR() {
        return real;
    }
    double getI() {
        return imag;
    }
    Complex operator+(const Complex &c2);
    Complex operator-(const Complex &c2);
    Complex operator*(const Complex &c2);
    Complex operator/(const Complex &c2);
    bool operator==(const Complex &c2);
    bool operator!=(const Complex &c2);
    Complex& operator=(const Complex &c1) {
        if (this != &c1) {          // 不允许自赋值
            this->real = c1.real;
            this->imag = c1.imag;
        }
        return *this;
    }
};

// 传递引用是为了少两次拷贝构造
Complex Complex::operator+(const Complex &c2) {
    Complex ret;
    ret.real = this->real + c2.real;
    ret.imag = this->imag + c2.imag;
    return ret;
}
Complex Complex::operator-(const Complex &c2) {
    Complex ret;
    ret.real = this->real - c2.real;
    ret.imag = this->imag - c2.imag;
    return ret;
}
Complex Complex::operator*(const Complex &c2) {
    Complex ret;
    double a = this->real, b = this->imag;
    double c = c2.real, d = c2.imag;

    ret.real = a * c - b * d;
    ret.imag = b * c + a * d;
    return ret;
}
Complex Complex::operator/(const Complex &c2) {
    Complex ret;
    double a = this->real, b = this->imag;
    double c = c2.real, d = c2.imag;
    ret.real = (a * c + b * d) / (c * c + d * d);
    ret.imag = (b * c - a * d) / (c * c + d * d);
    return ret;
}
bool Complex::operator==(const Complex &c2) {
    return this->real == c2.real && this->imag == c2.imag;
}
bool Complex::operator!=(const Complex &c2) {
    return this->real != c2.real || this->imag != c2.imag;
}

int main() {
    Complex c1(1, 2);
    Complex c2(2, 3);
    Complex c3;
    // c3 = c1 + c2;
    c3 = c1 + c2;
    cout << c3.getR() << "+" << c3.getI() << "i" << endl;
    c3 = c1 - c2;
    cout << c3.getR() << c3.getI() << "i" << endl;
    c3 = c1 * c2;
    cout << c3.getR() << "+" << c3.getI() << "i" << endl;
    bool ret = (c1 == c2);
    cout << ret << endl;
    ret = (c1 != c2);
    cout << ret << endl;

    Complex c4(1, 3);
    (c4 = c3) = c2;
    cout << c4.getR() <<  "+" << c4.getI() << "i" << endl;
    return 0;
}

