/*************************************************************************
	> File Name: write.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月02日 星期二 20时54分10秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdarg.h>
void get_time(char *time_str) {
    time_t timep;
    struct tm *ptm = NULL;
    time(&timep);
    ptm = localtime(&timep);
    sprintf(time_str, "[%04d-%02d-%02d %02d:%02d:%02d]", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
}
int write_log(char *log_path, const char *format, ...) {
    FILE *fp = fopen(log_path, "a+");
    char time_str[100];
    get_time(time_str);
    fprintf(fp, "%s", time_str);

    va_list arg;
    va_start(arg, format);
    int done = vfprintf(fp, format, arg);   //vfprintf()用法
    va_end(arg);
    fflush(fp);
    fclose(fp);
    return done;
}

int main(int argc, char **argv) {
    char *log_path = "/home/chongh/Homework/log_sys/test.log";
    char *format = "connect to %s success\n";
    char *host = "192.168.1.40";
    write_log(log_path, format, host);
    return 0;
}
