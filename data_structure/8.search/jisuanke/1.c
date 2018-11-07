/*************************************************************************
	> File Name: 1.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月07日 星期三 20时55分59秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 100000
#define MAXM 100

void to_lower(char *temp) {
    for (int i = 0; temp[i]; i++) {
        if (temp[i] >= 'A' && temp[i] <= 'Z') {
            temp[i] = temp[i] + 'a' - 'A';
        }
    }
    return ;
}

void sort(char str[][MAXM], int n) {
    for (int i = 0; i < n - 1; i++) {
        int times = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(str[j], str[j + 1]) > 0) {
                char temp[MAXM];
                strcpy(temp, str[j]);
                strcpy(str[j], str[j + 1]);
                strcpy(str[j + 1], temp);
                times = 1;
            }
        }
        if (times == 0) break;
    }
    return ;
}
int main() {
    int n, i;
    //printf("start\n");
    scanf("%d", &n);
  //  printf("n = %d\n", n);
    // 如何动态申请空间???
    char str[MAXN][MAXM];
    char temp[MAXM];
    for (i = 0; i < n; i++) {
        scanf("%s", temp);
        to_lower(temp);
//        printf("%s\n", temp);
        strcpy(str[i], temp);
    }
    sort(str, i);
    printf("No\n");
    for (int j = 1; j < i; j++) {
        if (strcmp(str[j], str[j - 1])) {
            printf("No\n");
        } else {
            printf("Yes\n");
        }
    }
    return 0;
}

