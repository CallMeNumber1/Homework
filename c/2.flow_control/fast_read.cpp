/*************************************************************************
	> File Name: fast_read.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月18日 星期二 20时31分09秒
 ************************************************************************/
// 快读, 与直接scanf差了大约25倍
#include <stdio.h>

char ss[1<<17], *A = ss, *B = ss;
// fread返回读入字符的个数
// A==B代表判断缓冲区是否为空,&&后面的条件用来判断是否读入了数据(当且仅当fread返回值为0时,逗号后面的A==B才成立)
inline char gc() {
    return A == B && (B = (A = ss) + fread(ss, 1, 1 << 17, stdin), A == B) ? -1 : *A++;
}

// 用模板的原因:使得既能处理int 也能处理long long等
template<typename T> inline void sdf(T &x) {
    char c;
    T y = 1;
    // 用来略过空格,和判断数字的符号
    while (c = gc(), (c < 48 || c > 57) && c != -1) {
        if (c == '-') y = -1;
    }
    // 当字符处于48('0')与57('9')之间时,与48异或(结果为0-9)就相当于减去48
    x = c ^ 48;
    while (c = gc(), (c <= 57 && c >= 48)) {
        // 相当于x * 2 + x * 8 + 数字
        // 即x * 10 + c - 48
        x = (x << 1) + (x << 3) + (c ^ 48);
    }
    x *= y;
}
int main() {
    //for (int i = 48; i <= 57; i++) {
    //    printf("%d ^ 48 = %d\n", i, i ^ 48);
    //}
    int n, a;
    sdf(n);
    //scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        sdf(a);
       // scanf("%d", &a);
    }
    return 0;
}
