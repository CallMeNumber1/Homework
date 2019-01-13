/*************************************************************************
	> File Name: strstr.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月13日 星期日 18时51分29秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <string.h>
using namespace std;


int strStr(char *haystack, char *needle) {
    int len = 0;
    int pos[256] = {0};
    memset(pos, -1, sizeof(pos));
    // 每一个字符在串中最后一个位置
    for (; needle[len]; len++) pos[needle[len]] = len;
    int i = 0, len2 = strlen(haystack);
    while (i + len <= len2) {
        int j = 0;
        // 这两位字符相等
        while (needle[j] && needle[j] == haystack[i + j]) ++j;
        // 匹配成功
        if (needle[j] == 0) return i;
        i += (len - pos[haystack[i + len]]);
    }
    return -1;
}

