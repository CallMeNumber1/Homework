/*************************************************************************
	> File Name: 5-1.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月17日 星期四 17时02分48秒
 ************************************************************************/

// 方法三：马拉车算法
int min(int a, int b) {
    return a < b ? a : b;
}
int max(int a, int b) {
    return a > b ? a : b;
}
int init(char *s, char *s_new) {
    s_new[0] = '$';
    s_new[1] = '#';
    int j = 2;
    for (int i = 0; s[i]; i++) {
        s_new[j++] = s[i];
        s_new[j++] = '#';
    }
    s_new[j] = '\0';
    return j;               // 返回s_new的长度
}

char *longestPalindrome(char *str) {
    int l = strlen(str);
    char *s_new = (char *)malloc(sizeof(char) * (l * 2 + 5));
    int *p = (int *)calloc(l * 2 + 5, sizeof(int));
    int len = init(str, s_new);       // 新字符串长度
    int max_len = -1;       // 最长回文长度
    int pos = 0;
    int id, mx = 0;
    for (int i = 1; i < len; i++) {
        if (i < mx) {
            p[i] = min(p[2 * id - 1], mx - i);
        } else p[i] = 1;
        // 不需要边界判断，因为左有'$',右有'\0'
        while (s_new[i - p[i]] == s_new[i + p[i]]) p[i]++;
        // 每走一步i，都要和mx比较
        // 我们希望mx尽可能走的远，这样才有机会执行if(i < mx)这句代码
        if (i + p[i] > mx) {
            id = i;
            mx = i + p[i];
        }
        if (max_len <= p[i] - 1) {
            max_len = p[i] - 1;
            pos = i;            
        }
    }
    int start = (pos - p[pos]) / 2;
    free(s_new);
    free(p);
    //printf("%d %d\n", max_len, (pos - p[pos]) / 2);
    str[start + max_len] = '\0';
    //printf("%s\n", str + (pos - p[pos]) / 2);
    return str + start;
    
}
