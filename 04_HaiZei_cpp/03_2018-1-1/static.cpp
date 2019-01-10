#include <iostream>

using namespace std;

class Test {
    private:
        static int cnt;
    public:
        Test() {
            cnt += 1;
        }
        ~Test() {
            cnt -= 1;
        }
        static int getCnt() {
            return cnt;
        }
        Test *getP() {
            return this;
        }
};
int Test::cnt = 0;
int main(){
    cout << Test::getCnt() << endl;
    Test t1;
    cout << t1.getCnt() << endl;

    cout << &t1 << endl;
    cout << t1.getP() << endl;
    
    Test t2;
    cout << t2.getCnt() << endl;
    Test t3;
    cout << t3.getCnt() << endl;
    Test *p = new Test;
    cout << Test::getCnt() << endl;
    delete p;
    cout << Test::getCnt() << endl;
    return 0;
}
