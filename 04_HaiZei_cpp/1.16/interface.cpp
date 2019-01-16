/*************************************************************************
	> File Name: interface.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月16日 星期三 14时40分23秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

class Interface {
    public:
        virtual bool open() = 0;
        virtual bool close() = 0;
        virtual bool send(char *buf, int len) = 0;
        virtual int receive(char *buf, int len) = 0;
}


int main() {

    
}
