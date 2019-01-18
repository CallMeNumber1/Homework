/*************************************************************************
	> File Name: try_catch.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 15时02分47秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;


int main() {
    try {
        try {
            throw 'a';
        } catch (int i) {
            cout << "catch(int i)" << i << endl;
            throw i;
        } catch (...) {
            cout << "catch(...)" << endl; 
            throw ;
        }
    } catch (char c) {
        cout << "information is : " << c << endl;
    } catch (...) {
        cout << "other exception" << endl;   
    }
    cout << "done" << endl;
    return 0;
}
