#include <iostream>

using namespace std;
class Test {
    private:
        int i, j;
        const int m;
    public:
        Test(int v) : m(10){
            this->i = v;
            this->j = 5;
        }
        int getI() {
            cout << "no const" << endl;
            return this->i;
        }
        int getI() const {
            cout << "const" << endl;
            return this->i;
        }
        void print() const {
            cout << "hello" << endl;
            return ;
        }
        int getM() const{
            print();
            return this->m;
        }
        void setM(int v) const{
            int *p = const_cast<int *>(&m);
            *p = v;
            return ;
        }
};
int main(){
   const Test t(1);
   cout << t.getM() << endl;
   t.setM(100);
   cout << t.getM() << endl;
   return 0;
}
