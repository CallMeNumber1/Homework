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
	//fseek(file, 0, SEEK_END);
	//int size = ftell(file);
	//rewind(file);
	//char *ar = (char *)malloc(sizeof(char)*size);
	//num_read = fread(ar, 1, size, file);
    //printf("%s", ar);
	//send(sock_client, ar, strlen(ar), 0);
    
    //system("bash disk.sh");
    char buf[MAX_SIZE + 1] = {0};
    // 用popen调用shell脚本，并将脚本输出输入管道
    FILE *pp = popen("bash disk.sh", "r");
    FILE *fp = fopen("testpp.txt", "w");
    while (fread(buf, 1, MAX_SIZE, pp) > 0) {
        buf[MAX_SIZE] = '\0';
        fwrite(buf, 1, strlen(buf), fp);
    } 
    pclose(pp);
    fclose(fp);

    while (num_read = fread(data, 1, MAX_SIZE, file) > 0) {
        // 需要手动添上字符串结束符
        data[MAX_SIZE] = '\0';
        send(sock_client, data, strlen(data), 0);
        printf("%s\n", data);
        memset(data, 0, sizeof(data));
    }
	
    close(sock_client);
    return 0;
}

