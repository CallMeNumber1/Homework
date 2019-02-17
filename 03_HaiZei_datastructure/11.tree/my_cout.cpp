/*************************************************************************
	> File Name: my_cout.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年02月17日 星期日 20时17分11秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

namespace mylib {
    class file {
    public:
        file(FILE *f) : f(f) {}
        file(const char *s) {
            this->f = fopen(s, "w");
        }
        FILE *get() const {  return this->f; }
        ~file() {
            if (this->f != NULL) fclose(this->f);
        }
    private:
        FILE *f;
    };

    class Character {
    public:
        Character(char c): c(c) {}
        char get() const{ return this->c; }; 
    private:
        char c;
    };
   class ostream {
    public:
       ostream() {
           this->fout = stdout;
       }
        ostream &operator<<(const int &x)  {
            fprintf(this->fout, "%d", x);
            return *this;
        }
        ostream &operator<<(const double &x) {
            fprintf(this->fout, "%lf", x);
            return *this;
        }
        ostream &operator<<(const char *x)  {
            fprintf(this->fout, "%s", x);
            return *this;
        }
       ostream &operator<<(const char x) {
           fprintf(this->fout, "%c", x);
           return *this;
       }
       ostream &operator<<(const Character &x) {
            (*this) << x.get();
           return *this;
       }
       ostream &operator<<(const file &x) {
           this->fout = x.get();
           return *this;
       }
    private:
       FILE *fout;
    };

    file STDIN(stdin), STDOUT(stdout), STDERR(stderr);
    Character endl('\n');
    ostream cout;
}

class A {
public :
    A(int x) : x(x) {}
    friend mylib::ostream &operator<<(mylib::ostream &out, const A &obj);
private:
    int x;
};

// 要想在自定义类型上使用，需要进行操作符<<重载
mylib::ostream &operator<<(mylib::ostream &out, const A &obj) {
    // 声明成友元，否则不能直接访问对象的私有成员
    out << "object : " << obj.x;
    return out;
}
int main() {
    A obj(123);
    mylib::cout << obj << " " << mylib::endl;
    mylib::file fout("output");
    mylib::cout << 123 << fout << 456 << mylib::STDOUT << 789 << mylib::endl;
    return 0;
}

