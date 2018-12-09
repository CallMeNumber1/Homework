/*************************************************************************
	> File Name: common.h
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年12月09日 星期日 16时55分56秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
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
#define INS 5
#define PORT 8080
pthread_mutex_t mut;
typedef struct mypara {
    char *s;
    //　传入参数标志是哪个线程
    int num;
} mypara;

typedef struct Node {
    struct sockaddr_in addr;
    int sockfd;
    struct Node *next;
} Node, *LinkedList;

int queue[INS + 1];
LinkedList linkedlist[INS + 1];
#endif
