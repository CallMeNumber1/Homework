/*************************************************************************
	> File Name: main2.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月04日 星期四 16时41分34秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>

char *error_msg = NULL;

int app_name_valid(int argc, char *argv[]) {
    int i = strlen(argv[0]);
    while (i > 0 && argv[0][i - 1] != '/') --i;
    int ret = strcmp(argv[0] + i, "haizeix") == 0;
    error_msg = (char *)(ret ? NULL : "wrong app-name");
    return ret;
}

int user_name_valid(char **env) {
    int ret = 0;
    for (char **p = env; p[0] != NULL; p++) {
        if (strncmp(p[0], "USER", 4)) continue;
        ret = strcmp(p[0], "USER=chongh") == 0;
    }
}
int main() {


    return 0;
}
