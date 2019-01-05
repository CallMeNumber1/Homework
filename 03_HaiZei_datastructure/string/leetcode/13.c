#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 128

int romanToInt(char* s) {
    #define BASE 'A'
    int vis[MAX] = {0};
    int ans = 0;
    for (int i = strlen(s) - 1; i >= 0; i--) {
        switch(s[i]) {
            case 'I': {
                if (vis['V' - BASE] || vis['X' - BASE]) {
                    ans -= 1;
                } else ans += 1;
            } break;
            case 'V': {
                vis['V' - BASE] = 1;
                ans += 5;
            } break;
            case 'X': {
                vis['X' - BASE] = 1;
                if (vis['L' - BASE] || vis['C' - BASE]) {
                    ans -= 10;
                } else ans += 10;
            } break;
            case 'L': {
                vis['L' - BASE] = 1;
                ans += 50;
            } break;
            case 'C': {
                vis['C' - BASE] = 1;
                if (vis['D' - BASE] || vis['M' - BASE]) {
                    ans -= 100;
                } else ans += 100;
            } break;
            case 'D': {
                vis['D' - BASE] = 1;
                ans += 500;
            } break;
            case 'M': {
                vis['M' - BASE] = 1;
                ans += 1000;
            } break;
        }    
    }
    return ans;
}



int main(){
    char str[100];
    while (scanf("%s", str) != EOF) {
        int ans = romanToInt(str);
        printf("ans: %d\n", ans);
    }
   
    return 0;
}
