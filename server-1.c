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
#define MAX_SIZE 1024
int main(int argc, char *argv[]) {
    int a = 0;
    //int server_listen;
    int sockfd, port, pid;
    struct sockaddr_in server_listen;
    int sockfd1;
    //if (argc != 2) {
      //  printf("Usage: ./tcp_server port\n");
       // exit(0);
   // }
    
    //port = atoi(argv[1]);
    
    if ((sockfd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        return -1;
    }

    memset(&server_listen, 0, sizeof(server_listen));
    server_listen.sin_family = AF_INET;
    server_listen.sin_addr.s_addr = htonl(INADDR_ANY);
    server_listen.sin_port = htons(DEFAULT_PORT);
    
    if (bind(sockfd1, (struct sockaddr*)&server_listen, sizeof(server_listen)) < 0) {
        perror("bind");
        return -1;
    }
    if (listen(sockfd1, 20) < 0) {
        perror("listen");
        return -1;
    }
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        if ((sockfd = accept(sockfd1, (struct sockaddr *)&client_addr, &len)) < 0) {
            break;
        }
        if ((pid = fork()) < 0)
            printf("Error forking child process");
        if (pid == 0) {
            close(sockfd1);
            char buffer[MAX_SIZE];
            // recv返回值为0,说明对方已关闭连接,因此自己也关闭,然后退出子进程,父进程什么也不做,再从accpet开始
            while ((a = recv(sockfd, buffer, MAX_SIZE, 0)) > 0) {
               buffer[a] = '\0';
                printf("%s:%d : recv %d 字节 %s\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port), a, buffer);
                // 清空输出缓冲区,并把缓冲区内容输出
                fflush(stdout);
                memset(buffer, 0, sizeof(buffer));
            }
            printf("\n");
            close(sockfd);
            exit(0);
        }
        close(sockfd);
    }

    return 0;
}

