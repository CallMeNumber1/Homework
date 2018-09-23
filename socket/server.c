/*************************************************************************
	> File Name: server.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月23日 星期日 22时27分12秒
 ************************************************************************/

#include <netinet/in.h>
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


#define DEFAULT_PORT 8000
#define MAXLINE 4096
int main() {
    int sockfd, confd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    int n;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        return -1;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // IP地址 让系统自动获取本机IP地址
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(DEFAULT_PORT);
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind");
        return -1;
    }
    if (listen(sockfd, 10) == -1) {
        perror("listen");
        return -1;
    }
    printf("======waiting for client's request=====\n");
    while (1) {
        // 阻塞直到有客户端连接
        if ((confd = accept(sockfd, (struct sockaddr*)NULL, NULL)) == -1) {
            perror("accept");
            return -1;
        }
        // 接收客户端传过来的数据
        n = recv(confd, buff, MAXLINE, 0);
        buff[n] = '\0';
        printf("rect msg from client:\n %s\n", buff);
        close(confd);
    }
    close(sockfd);
    return 0;
}
