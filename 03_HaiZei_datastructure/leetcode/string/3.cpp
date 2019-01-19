/*************************************************************************
	> File Name: atoi.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月13日 星期日 18时28分12秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int atoi(char *str) {
    int i = 0, ret = 0, flag = 1, pre_ret;
    while (str[i] == ' ') ++i;
    // 找到第一个非空格字符
    if (str[i] == '-') flag = -1, i++;
    else  if (str[i] == '+') i++;
    while (str[i] && str[i] <= '9' && str[i] >= '0') {
        pre_ret = ret;
        ret = ret * 10 + (str[i] - '0');
        // 判断是否溢出
        // 因为负数最值比正数最值大（无符号时)
        // 但此种方法处理时仍然不会出错,因为仍会返回INT_MIN
        if (ret / 10 != pre_ret) { 
            return flag == -1 ? INT_MIN : INT_MAX;
        }
        i++;
    }
    return ret * flag;
}



int main() {
       
    return 0;
}
