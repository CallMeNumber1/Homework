/*************************************************************************
	> File Name: server.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月23日 星期日 22时27分12秒
 ************************************************************************/
// 接收客户端传来的文件,打印到屏幕
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


#define DEFAULT_PORT 8080
#define MAX_SIZE 1024

int socket_create(int port);                //建立监听状态套接字
int main(int argc, char *argv[]) {
    int a = 0;
    int confd, pid;
    int sockfd = socket_create(DEFAULT_PORT);
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        // 每来一个请求就创建一个新的套接字,创建一个子进程来处理
        if ((confd = accept(sockfd, (struct sockaddr *)&client_addr, &len)) < 0) {
            break;
        }
        if ((pid = fork()) < 0)                     //创建一个子进程,当pid为0时说明在执行子线程
            printf("Error forking child process");
        if (pid == 0) {
            close(sockfd);
            char buffer[MAX_SIZE + 1] = {0};
            // recv返回值为0,说明对方已关闭连接,因此自己也关闭,然后退出子进程,父进程什么也不做,再从accpet开始
            while ((a = recv(confd, buffer, MAX_SIZE, 0)) > 0) {
               buffer[a] = '\0';
                printf("%s:%d : recv %d 字节 %s\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port), a, buffer);
                // 清空输出缓冲区,并把缓冲区内容输出
                fflush(stdout);
                memset(buffer, 0, sizeof(buffer));
            }
            printf("\n");
            close(confd);
            exit(0);
        }
        close(confd);
    }
    close(sockfd);
    return 0;
}
int socket_create(int port) {
    struct sockaddr_in server_listen;
    int sockfd;
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {               // 创建一个套接字
        perror("Socket");
        return -1;
    }

    memset(&server_listen, 0, sizeof(server_listen));
    server_listen.sin_family = AF_INET;
    server_listen.sin_addr.s_addr = htonl(INADDR_ANY);                  // 监听所有的IP地址
    server_listen.sin_port = htons(DEFAULT_PORT);                       // 监听的端口
    
    // 指定要监听的端口
    if (bind(sockfd, (struct sockaddr*)&server_listen, sizeof(server_listen)) < 0) {
        perror("bind");
        return -1;
    }
    if (listen(sockfd, 20) < 0) {                                       // 同一时刻可以处理20个请求
        perror("listen");                                               // 将套接字设为监听状态
        return -1;
    }
    return sockfd;    
}
