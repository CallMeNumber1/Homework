/*************************************************************************
	> File Name: socket.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年09月23日 星期日 16时40分24秒
 ************************************************************************/

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

#define MAXLINE 4096
int main(int ac, char *av[]) {
    int sockfd, n, rec_len;
    int i_port = 8000;
    char sendLine[MAXLINE];
    char buf[MAXLINE];
    char *c_ipaddr = "192.168.1.91";
    struct sockaddr_in servaddr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("error");
        exit(0);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(i_port);
    if (inet_pton(AF_INET, c_ipaddr, &servaddr.sin_addr) <= 0) {
        perror("error2");
        exit(0);
    }
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)  {
        perror("error3");
        exit(0);
    }
    while (1) {
    fgets(sendLine, 4096, stdin);
    if (send(sockfd, sendLine, strlen(sendLine), 0) < 0) {
        perror("error4");
        exit(0);
    }
    }

    
    return 0;
}
