/*************************************************************************
	> File Name: main.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月04日 星期四 15时53分13秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *env[]) {
    char *user = getenv("USER");
    char *fname = strrchr(argv[0], '/');
    if (fname == NULL) strcpy(fname, "haizeix");
    else fname++;

    if (strcmp(user, "chongh") == 0 && strcmp(fname, "haizeix") == 0) printf("success!\n");
    else printf("failed!\n");
        
    /*
    for (char **p = env; p[0] != NULL; p++) {
        printf("%s\n", p[0]);
    }
    */
    return 0;
}
