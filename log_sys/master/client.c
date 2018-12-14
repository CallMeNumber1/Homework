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


#define MAX_SIZE 4096
#define PORT 8000
int socket_create(int port);
int main(int argc, char *argv[]) {
    int sock_client;
    char buffer[MAX_SIZE];
    struct sockaddr_in dest_addr;
    int port = atoi(argv[2]);
    char *host = argv[1];
    if ((sock_client = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        exit(0);
        return -1;
    }
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(host);
    if (connect(sock_client, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("Connect");
        exit(0);
        return -1;
    }
    int recv_socket = socket_create(1234);
    int confd;
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        if ((confd = accept(recv_socket, (struct sockaddr*)&client_addr, &len)) == -1) {
            perror("accept");
            return -1;
        }
        char *temp = inet_ntoa(client_addr.sin_addr);
        printf("receive connect from server:%s\n", temp);
        char code[4];
        while ((len = recv(confd, code, 3, 0)) > 0) {
            code[3] = '\0';
            if (strcmp(code, "100") == 0) {
                // 表示接受到了master对于cpu信息的请求
                // 回复200表示存在cpu信息文件
                // TODO:回复400表示不存在cpu信息文件, 进入另外的业务逻辑
                // TODO:master每要求一种日志文件,是否都要新建一个监听端口?
                printf("accept requst code 100\n");
                strcpy(code, "200\0");
                send(confd, code, strlen(code), 0);
                // 这里是否需要新建一个监听状态的套接字
                int data_sockfd = socket_create(6666), data_confd;
                struct sockaddr_in data_client_addr;
                socklen_t len = sizeof(data_client_addr);
                if ((data_confd = accept(data_sockfd, (struct sockaddr*)&data_client_addr, &len)) == -1) {
                    perror("accept");
                    return -1;
                }
                // 为何输出对方的IP为0.0.0.0 和上面不一致
                // 在增加`socklen_t len = sizeof(data_client_addr)`后问题解决
                printf("begin send sysinfo to %s\n", inet_ntoa(data_client_addr.sin_addr));
                char buf[MAX_SIZE + 1] = {0};
                FILE *p1 = popen("bash sysinfo/check_cpu.sh", "r");
                while (fread(buf, 1, MAX_SIZE, p1) > 0) {
                    buf[MAX_SIZE] = '\0';
                    send(data_confd, buf, strlen(buf), 0);
                    printf("data:%s\n", buf);
                    memset(buf, 0, sizeof(buf));
                }
                pclose(p1);
                close(data_confd);
                close(data_sockfd);
            } else {
                printf("code = %s\n", code);
            }
        }
    }
    /*
    while (1) {
        scanf("%[^\n]s", buffer);
        getchar(); //吸收回车
        send(sock_client, buffer, strlen(buffer), 0);
    }
    */
    close(sock_client);
    return 0;
}
int socket_create(int port) {
    int socket_server, sockfd;
    struct sockaddr_in s_addr, c_addr;
    socklen_t len;
    if ((socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                perror("socket create");
                return -1;
            
    }
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    printf("port:%d\n", s_addr.sin_port);
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

