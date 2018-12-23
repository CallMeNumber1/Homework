/*************************************************************************
	> File Name: client.h
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年12月21日 星期五 22时24分04秒
 ************************************************************************/

#ifndef _CLIENT_H
#define _CLIENT_H
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <io.h>
typedef struct mypara {
    char *s;
    //　传入参数标志是哪个线程
    int num;
} mypara;
#endif
