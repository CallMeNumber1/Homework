/*************************************************************************
	> File Name: polymorphic.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月16日 星期三 09时40分05秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;
class Parent {
    public:
    virtual void say() {
        cout << "I'm Parent" << endl;
    }
};
class Child : public Parent {
    public:
    void say() {
        cout << "I'm Child" << endl;
    }
};

void how_to_say(Parent *p) {
    p->say();
    return ;
};


int main() {
    Parent p;
    Child c;
    p.say();
    c.say();
    how_to_say(&p);
    how_to_say(&c);


    return 0;
}
