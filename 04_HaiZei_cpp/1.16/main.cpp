/*************************************************************************
	> File Name: main.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月16日 星期三 09时14分02秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;


class People {
    private:
        string name;
        int age;
    public:
    People(string s1, int v1): name(s1), age(v1) {

    }
    void print() {
        cout << name << " " << age << endl;
    }
};

class Teacher: virtual public People {
    public:
    Teacher(string s1, int v1) : People(s1, v1) {

    }
};
class Student : virtual public People {
    public:
    Student(string s1, int v1) : People(s1, v1) {

    }
};

class Doctor: public Teacher, public Student {
    public:
    Doctor (string s1, int v1) : Teacher(s1 + "1", v1 + 1), Student(s1 + "2", v1 + 2), People(s1, v1) {

    }
};

int main() {
    Doctor d("qwe", 28);
    d.Teacher::print();
    d.Student::print();
    d.print();
    return 0;
}
