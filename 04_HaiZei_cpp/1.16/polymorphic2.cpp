/*************************************************************************
	> File Name: polymorphic2.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月16日 星期三 09时57分50秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class BossA {
    public:
    int battle() {
        int ret = 10;
        cout << "CompanyA::battle = " << ret << endl;
        return ret;
    }

};
class BossB {
    public:
    virtual int fight() {
        int ret = 8;
        cout << "CompanyB::fight = " << ret << endl;
        return ret;
    }
   
};
class NewBoss: public BossB {
    public:
    int fight() {
        // 调用父类的方法 this可省略
        int ret = this->BossB::fight() * 2; 
        cout << "NewBoss:: fight = " << ret << endl;
        return ret;
    }
};
void vs(BossA *c1, BossB *c2) {
    int a = c1->battle();
    int b = c2->fight();
    if (a > b) {
        cout << "Company A is winner" << endl;
    } else {
        cout << "Company B is winner" << endl;
    }
}

int main() {
    BossA c1;
    BossB c2;
    vs(&c1, &c2);
    cout << "one year later" << endl;
    NewBoss nb;
    vs(&c1, &nb);
    return 0;
}
