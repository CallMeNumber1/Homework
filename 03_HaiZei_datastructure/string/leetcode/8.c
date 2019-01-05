#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define INT_MAX 2147483647
#define INT_MIN -2147483648
int myAtoi(char* str) {
    if (strlen(str) == 0) return 0;         // empty
    int i = 0, flag = 1;
    while (str[i] == ' ') {
        str++;
    }
    if (!(str[0] == '+' || str[0] == '-' || str[0] >= '0' && str[0] <= '9')) return 0;
    i = 0;
    if (str[i] == '-') {
        str++;
        flag = -1;
    } else if (str[i] == '+') str++;
    while (str[i] == '0') str++;        // 删掉首部的所有0字符
    
    int *ans = (int *)malloc(sizeof(int) * strlen(str));
    int k = 0;
    // 将字符串中的有效数字存到整型数组里
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9') break;
        ans[k++] = str[i++] - '0';
    }
    int res = 0;
    if (k > 10) {
        return (flag == 1) ? INT_MAX : INT_MIN;
    } else if (k == 10){
        int min[10] = {2, 1, 4, 7, 4, 8, 3, 6, 4, 8};
        int max[10] = {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
        if (flag == 1) {
            long long ll = 0;
            for (int i = 0; i < k; i++) {
                ll = ll * 10 + ans[i]; 
            }
            if (ll >= INT_MAX) return INT_MAX;
            else res = (int)ll;
        } else {
            long long ll = 0;
            for (int i = 0; i < k; i++) {
                ll = ll * 10 + ans[i]; 
            }
            if (ll >= -INT_MIN) return -INT_MIN;
            else res = (int)ll;
        }
    } else {
        for (int i = 0; i < k; i++) {
            res = res * 10 + ans[i]; 
        }
    }
    // printf("k:%d\n", k);
    // for (int i = 0; i < k; i++) {
    //     printf("%d ", ans[i]);
    // }
    return res * flag;
}
int main(){
   char str[100] = {0};
   while (scanf("%s", str) != EOF) {
       printf("%d\n", myAtoi(str));
   }
   char a = 'a';
   char A = 'A';
   
   return 0;
}
