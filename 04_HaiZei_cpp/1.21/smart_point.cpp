/*************************************************************************
	> File Name: smart_point.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月21日 星期一 18时39分32秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class Test {
    private:
        int i;
    public:
    Test(int i = 0) {
       this->i = i;
    }
    int getI() {
        return this->i;
    }
};

class SmartPoint {
    private:
        Test *mp;
    public:
    SmartPoint(Test *p = NULL) {
        mp = p;
    }
    SmartPoint(const SmartPoint &obj) {
        mp = obj.mp;
        // 因为const是只读的，不能改变
        // 因此先进行类型转换
        const_cast<SmartPoint&>(obj).mp = NULL;
    }
    Test *operator->() {
        return mp;    
    }
    // 因为可以用来赋值作为左值，所以返回引用
    Test& operator*() {
        return *mp;
    }
    SmartPoint& operator=(const SmartPoint &obj) {
        if (this != &obj) { // 先排除自赋值的情况
            delete mp;
            mp = obj.mp;
            const_cast<SmartPoint&>(obj).mp = NULL;
        }
        return *this;
    }
    ~SmartPoint() {
        cout << "~SmartPoint" << endl;
        delete mp;

    }
};

int main() {
    for (int i = 0; i < 5; i++) {
        SmartPoint p = new Test(i);
        cout << p->getI() << endl;
    }
    SmartPoint p1(new Test(1));
    SmartPoint p2(new Test(2));
    p1 = p2;

    return 0;
}
