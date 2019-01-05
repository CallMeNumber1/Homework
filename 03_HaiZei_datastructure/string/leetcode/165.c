#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int dotCnt(char *version) {
    int cnt = 0;
    for (int i = 0; version[i]; i++) {
        if (version[i] == '.') cnt++;
    }
    return cnt;
}

int compareVersion(const char* version1, const char* version2) {
    const char *s1 = version1, *s2 = version2;
    int i = 0, j = 0;
    while (s1[i] && s2[j]) {
        int v1 = 0, v2 = 0;
        while (s1[i] && s1[i] != '.') {
            v1 = s1[i] - '0' + v1 * 10;
            i++;
        }
        while (s2[j] && s2[j] != '.') {
            v2 = s2[j] - '0' + v2 * 10;
            j++;
        }
        if (v1 > v2) {
            return 1;
        } else if (v1 == v2) {
            if (s1[i]) i++;
            if (s2[j]) j++;
        } else {
            return -1;
        }
        printf("i=%d, j=%d\n", i, j);
        printf("v1=%d, v2=%d\n", v1, v2);
    }
    
    while (s1[i++]) {
        if (s1[i] == '.') continue;
        if (s1[i] != '0') {
            return 1;
        }
    }
    while (s2[j++]) {
        if (s2[j] == '.') continue;
        if (s2[j] != '0') {
            return -1;
        }
    }
    return 0;
}
int compareVersion1(const char* version1, const char* version2) {
	const char *v1 = version1, *v2 = version2;
	while (v1 != NULL || v2 != NULL) {
		int i1 = v1 == NULL ? 0 : atoi(v1), i2 = v2 == NULL ? 0 : atoi(v2);
		if (v1 != NULL) v1 = strstr(v1, ".");
		if (v1 != NULL) ++v1;
		if (v2 != NULL) v2 = strstr(v2, ".");
		if (v2 != NULL) ++v2;
		if (i1 < i2) return -1;
		if (i2 < i1) return 1;
	}
	return 0;
}
int main(){
    char str1[100], str2[100];
    while (scanf("%s%s", str1, str2) != EOF) {
        printf("%d\n", compareVersion(str1, str2));
        // memset(str1, 0, sizeof(str1));
        // memset(str2, 0, sizeof(str2));
    }
   
   return 0;
}
