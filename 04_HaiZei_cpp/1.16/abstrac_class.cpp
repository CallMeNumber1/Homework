/*************************************************************************
	> File Name: abstrac_class.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月16日 星期三 19时08分17秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class Shap {
public:
    virtual double area() = 0;    
};

class Rect: public Shap {
private:
    double h;
    double w;
public:
    Rect(double v1, double v2) {
        h = v1;
        w = v2;
    }
    double area() {
        return h * w;
    }
};
class Circle: public Shap {
private:
    double r;
public:
    Circle(double v) {
        r = v;
    }
    double area() {
        return 3.14 * r * r;
    }
};
int main() {
    Rect r(3.2, 4.5);
    Circle c(0.6);
    cout << r.area() << endl;
    cout << c.area() << endl;
}

