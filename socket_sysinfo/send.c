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

#define MAX_SIZE 1024
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
    FILE *file = fopen("/home/chongh/Linux/s.c", "r");
    if (file == NULL) {
        printf("open error\n");
        return 0;
    }
    char data[MAX_SIZE + 1] = {0};
    int num_read;
    
    //system("bash disk.sh");
    // 用popen来执行shell脚本,并将相应脚本信息发送到服务器端,用字符串的第一个位置来标志发送的是关于哪个脚本的信息
    char buf[MAX_SIZE + 2] = {0};
    FILE *p1 = popen("bash check_cpu.sh", "r");
    FILE *fp = fopen("testpp.txt", "w");
    while (fread(buf + 1, 1, MAX_SIZE, p1) > 0) {
        buf[0] = '0';   //标志当前发送的是磁盘信息
        buf[MAX_SIZE + 1] = '\0';
        fwrite(buf, 1, strlen(buf), fp);
        send(sock_client, buf, strlen(buf), 0);
        memset(buf, 0, sizeof(buf));
    }
    pclose(p1);
    fclose(fp);

    p1 = popen("bash disk.sh", "r");
    fp = fopen("testpp2.txt", "w");
    while (fread(buf + 1, 1, MAX_SIZE, p1) > 0) {
        buf[0] = '1';   //标志发送的是disk信息
        buf[MAX_SIZE + 1] = '\0';
        fwrite(buf, 1, strlen(buf), fp);
        send(sock_client, buf, strlen(buf), 0);
        memset(buf, 0, sizeof(buf));
    }
    pclose(p1);
    fclose(fp);
    
    p1 = popen("bash check_memory.sh", "r");
    fp = fopen("testpp3.txt", "w");
    while (fread(buf + 1, 1, MAX_SIZE, p1) > 0) {
        buf[0] = '2';   //标志发送的是mem信息
        buf[MAX_SIZE + 1] = '\0';
        fwrite(buf, 1, strlen(buf), fp);
        send(sock_client, buf, strlen(buf), 0);
        memset(buf, 0, sizeof(buf));
    }
    pclose(p1);
    fclose(fp);
    
    close(sock_client);
    return 0;
}

