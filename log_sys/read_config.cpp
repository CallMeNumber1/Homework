/*************************************************************************
	> File Name: read.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月02日 星期二 20时20分16秒
 ************************************************************************/
// 读取配置文件,执行时给定配置文件的路径和要找的配置字段名,输出配置的值

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int get_conf_value(char *path_name, char *key_name, char *value) {
    FILE *fp = fopen(path_name, "r");
    if (fp == NULL) {
        perror("error open file");
        exit(0);
    }
    int read_cnt;
    char *line = NULL;
    size_t len = 0;
    while ((read_cnt = getline(&line, &len, fp)) != -1) {
        int lenb = strlen(key_name);
        value = strstr(line, key_name);  //如果找不到子串则返回NULL
        if (value == NULL) continue;     //找到则返回第一次出现的位置 
        value = value + lenb + 1;        //额外加1用来跳过'='号
        printf("%s is %s", key_name, value);
    }
}
int main(int argc, char **argv) {
    char *path_name = argv[1];
    char *key_name = argv[2];
    char *value = NULL;
    get_conf_value(path_name, key_name, value);
    return 0;
}
