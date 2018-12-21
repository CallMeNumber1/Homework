/*************************************************************************
	> File Name: 1.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月03日 星期六 11时06分45秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main() {
    char q1[10][12];
    char q2[10][12];
    char q3[10][12];
    int temp;
    char str[12];
    for (int i = 0; i < 10; i++){
        strcpy(q1[i], "0");
        strcpy(q2[i], "0");
        strcpy(q3[i], "0");
    }
    int i1 = 0, i2 = 0, i3 = 0;
    while (scanf("%d%s", &temp, str) != EOF) {
        switch (temp) {
            case 0:
                strcpy(q1[i1++], str);
                break;
            case 1:
                strcpy(q2[i2++], str);
                break;
            case 2:
                strcpy(q3[i3++], str);
                break;
        }
    }
    for (int i = 0; i < 10; i++) {
        printf("%s %s %s\n", q1[i], q2[i], q3[i]);
    }
    return 0;

}

