/*************************************************************************
	> File Name: delete_node.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年12月09日 星期日 19时55分21秒
 ************************************************************************/

#include <stdio.h>
#include "delete_node.h"
Node delete_node(Node *head, int para_num, struct sockaddr_in old) {
    printf("\033[31m-----Delete begining-----\033[0m\n");
    Node ret, *p;
    ret.next = head;
    p = &ret;
    printf("delete %s success\n", inet_ntoa(old.sin_addr));
    if (queue[para_num] == 1) {
        ret.next = NULL;
    } else {
        while (p->next->addr.sin_addr.s_addr != old.sin_addr.s_addr && p) {
            p = p->next;
        }
        p->next = p->next->next;
    }
    return ret;
}

