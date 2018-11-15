/*************************************************************************
	> File Name: send_response.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月13日 星期二 18时08分47秒
 ************************************************************************/

#include <stdio.h>

int send_response(int sockfd, int rq) {
    if (send(sockfd, &rq, sizeof(rq), 0) <= 0) {
        perror("send_response");
    }
}

int main() {

    return 0;
}
