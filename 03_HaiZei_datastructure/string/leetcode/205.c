#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




int isIsomorphic(char* s, char* t) {
    #define MAX 128
    if (strlen(s) != strlen(t)) return 0;
    int num[MAX] = {0};             // 记录每个字符分别是第几个新出现的字符
    int vis[MAX] = {0};
    // 用数组记录字符的出现规律
    int *patternS = (int *)calloc(strlen(s) + 1, sizeof(int));
    int *patternT = (int *)calloc(strlen(t) + 1, sizeof(int));
    int k = 0, l = 0;
    for (int i = 0; s[i]; i++) {
        // 是否为新出现的字符
        if (!vis[s[i]]) {
            vis[s[i]] = 1;
            num[s[i]] = ++k;
            patternS[i] = num[s[i]];
        } else patternS[i] = num[s[i]];
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 0; t[i]; i++) {
        if (!vis[t[i]]) {
            vis[t[i]] = 1;
            num[t[i]] = ++l;
            patternT[i] = num[t[i]];
        } else patternT[i] = num[t[i]];
    }
    
    // for (int i = 0; i < strlen(s); i++) {
    //     printf("%d", patternS[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < strlen(t); i++) {
    //     printf("%d", patternT[i]);
    // }
    
    int flag = 1;
    for (int i = 0; i < strlen(s) && flag; i++) {
        if (patternS[i] == patternT[i]) continue;
        flag = 0;
    }
    return flag;
}
int main(){
    char s1[15000] = {0}, s2[15000] = {0};
   while (scanf("%s%s", s1, s2) != EOF) {
       printf("%d\n", isIsomorphic(s1, s2));
   }
   
   return 0;
}
