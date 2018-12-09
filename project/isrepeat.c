/*************************************************************************
	> File Name: is_repeat.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年12月09日 星期日 20时03分46秒
 ************************************************************************/

#include <stdio.h>
#include "isrepeat.h"
// 检查是否已存在这个IP
int isrepeat(struct sockaddr_in new) {
    int flag = 0;
    for (int i = 0; i < INS && !flag; i++) {
        Node *p = linkedlist[i];
        while (p && !flag) {
            if (new.sin_addr.s_addr == p->addr.sin_addr.s_addr) flag = 1;
            p = p->next;
        }
    }
    return flag;
}

