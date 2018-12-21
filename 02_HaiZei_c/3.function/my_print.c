/*************************************************************************
	> File Name: my_print.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月20日 星期四 22时54分44秒
 ************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>
char str[25];
void print(int num) {
    if (num == 0) {
        putchar('0');
    } else if (num < 0) {
        putchar('-');
        num *= -1;
        int digit = 0;
        while (num) {
            str[digit++] = num % 10 + '0';
            num /= 10;
        }
        for (int i = digit - 1; i >= 0; i--) {
            putchar(str[i]);
        }

    } else {
        int digit = 0;
        while (num) {
            str[digit++] = num % 10 + '0';
            num /= 10;
        }
        for (int i = digit - 1; i >= 0; i--) {
            putchar(str[i]);
        }
    }
}
int print_int(int x, int flag) {
    if (x == 0) {
        flag && putchar('0');
        return flag;
    }
    int temp = x, ret = 0;
    x = 0;
    while (temp) {
        x = x * 10 + temp % 10;
        temp /= 10;
    }
    while (x) {
        putchar(x % 10 + '0');
        ret++;
        x /= 10;
    }
    return ret;
}
int my_print(const char *frm, ...) { 
    int cnt = 0;
    va_list arg;
    va_start(arg, frm);
    for (int i = 0; frm[i]; i++) {
        switch (frm[i]) {
            case '%' : {
                i++;
                switch (frm[i]) {
                    case 'd' : {
                        int temp = va_arg(arg, int);
                        int p1 = temp / 10, p2 = temp % 10;
                        if (p1 < 0) {
                            putchar('-'), cnt++;
                            p1 = -p1, p2 = -p2;
                        }
                        cnt += print_int(p1, 0);
                        cnt += print_int(p2, 0);
                    } break;
                    default :
                        fprintf(stderr, "error : unknown %%%c\n", frm[i]);
                        exit(1);
                }
            } break;
            default : 
                putchar(frm[i]);cnt++;
        }
    }
    return cnt;
}
int main() {
    int n = 123;
    // 测试能正常返回输出字符个数
    //my_print("\ndigit = %d\n", my_print("hello"));
    my_print("hello world\n");
    my_print("n = %d\n", n);
    my_print("n = %d\n", 12000);
    my_print("n = %d\n", -567);
    my_print("n = %d\n", INT32_MIN);
    my_print("n = %d\n", INT32_MAX);
    return 0;
}
