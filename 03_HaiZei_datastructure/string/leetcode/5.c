#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100

// 是回文则返回长度, 不是则返回-1
int isPalindrome(char *s, int l, int r) {
    int len = r - l + 1;
    int flag = r - l + 1;
    for (int i = l, k = 1; i <= l + len / 2; i++, k++) {
        if (s[i] == s[l + len - k]) continue;
        flag = -1;
        break;
    }
    return flag;
}
char* longestPalindrome(char* s) {  
    int ans = 0;
    int l = 0, r = 0;
    for (int i = 0; s[i]; i++) {
        for (int j = i; s[j]; j++) {
            int temp = isPalindrome(s, i, j);
            if (temp > ans) {
                ans = temp;
                l = i;
                r = j;
            }
        }
    }
    s[r + 1] = '\0';
    return s + l;
}

int main(){
    char str[MAX + 5];
    scanf("%s", str);
    printf("%s\n", longestPalindrome(str));
    return 0;
}
