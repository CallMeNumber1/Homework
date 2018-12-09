/*************************************************************************
	> File Name: socket_create.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年12月09日 星期日 17时01分27秒
 ************************************************************************/

#include <stdio.h>
#include "common.h"
#include "socket_create.h"
int socket_create(int port) {
    int socket_server;
    struct sockaddr_in s_addr;
    if ((socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket create");
        return -1;
    }
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    s_addr.sin_addr.s_addr = htons(INADDR_ANY);
    
    int opt = 1;
    setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));


    if ((bind(socket_server, (struct sockaddr*)&s_addr, sizeof(struct sockaddr))) < 0) {
        perror("bind");
        return -1;
    }
    if (listen(socket_server, 10) < 0) {
        perror("listen");
        return -1;
    }
    return socket_server;
}
