/*************************************************************************
	> File Name: exception1.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月18日 星期五 14时43分45秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;


int main() {
    // 严格匹配,不会进行类型转换
    // 且catch(...)只能放到最后
    try {
        throw 1;
    } catch (char c) {
        cout << "catch(char c)" << endl;
    } catch (short s) {
        cout << "catch(short s)" << endl;
    } catch (double d) {
        cout << "catch(double d)" << endl;
    } catch (int i) {
        cout << "catch(int i)" << endl;
    } catch (...) {
        cout << "catch(...)" << endl;
    }
    return 0;
}
