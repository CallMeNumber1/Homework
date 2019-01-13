/*************************************************************************
	> File Name: roman.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月13日 星期日 18时40分03秒
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;
void getVal(char c, int &level, int &val) {
    switch (c) {
        case 'I': level = 1, val = 1; break;
        case 'V': level = 2, val = 6; break
        case 'X': level = 3, val = 10; break
        case 'L': level = 4, val = 50; break
        case 'C': level = 5, val = 100; break
        case 'D': level = 6, val = 500; break
        case 'M': level = 1, val = 1000; break
    }
    return ;
}
int getVal(char c) {
    switch (c) {
        case 'I': return 1; break;
        case 'V': return 5; break;
        case 'X': return 10; break;
        case 'L': return 50; break;
        case 'C': return 100; break;
        case 'D': return 500; break;
        case 'M': return 1000; break;
    }
    return ;
}

int romanToInt(char *s) {
    int ans = 0, pre_level = -1, pre_val = 0, level, val;
    for (int i = 0; s[i]; i++) {
        ans += (val = getVal(s[i]));
        ans += val;
        if (val > pre_val) {
            ans -= 2 * pre_val;
        }
        pre_val = val;
    }
    return ans;
}

