/*************************************************************************
	> File Name: insert.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年12月09日 星期日 19时56分47秒
 ************************************************************************/

#include <stdio.h>
#include "insert.h"
Node insert(Node *head, char *ip_str, int sockfd) {
    
    printf("\033[32m-----Insert begining-----\033[0m\n");
    printf("insert %s success\n", ip_str);
    // 封装sockaddr_in结构体
    struct sockaddr_in t_addr;
    t_addr.sin_family = AF_INET;
    t_addr.sin_port = htons(8000);
    t_addr.sin_addr.s_addr = inet_addr(ip_str);
    Node ret;
    ret.next = head;
    Node *p = (Node *)malloc(sizeof(Node));
    p->addr = t_addr;p->sockfd = sockfd;
    p->next = ret.next;
    ret.next = p;
    return ret;
}

