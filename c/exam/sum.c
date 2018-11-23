/*************************************************************************
	> File Name: sum.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年11月23日 星期五 14时39分03秒
 ************************************************************************/

#include <stdio.h>
#define MAX 25
int num[MAX];
int vis[MAX] = {0};
int ans[MAX] = {0};
int n, T, cnt = 0;

int is_valid() {
    int flag = 0;
    for (int i = 0; i < n; i++) {
        if (vis[i] == 1) {
            flag = 1;
            break;
        }
    }
    return flag;
}

// step从最后一个数开始,t记录了已经选了几个数
void dfs(int step, int sum, int t) {
    if (step < 0) {
        if (sum == T) {
            // 因为有可能出现一个数字都没选，而sum与T相等的情况
            // 因此要先判断是否一个数字都没选的情况
            if (!is_valid()) return; 
            // 因为是倒着找的,所以要倒着输出
            cnt++;
            for (int i = t - 1; i >= 0; i--) {
                printf("%d ", ans[i]);
            }
            printf("\n");
        }
        return ;
    }
    // 先搜索不含最后一个的,再搜索包含第一个的
    dfs(step - 1, sum, t);
    vis[step] = 1;
    ans[t] = num[step];
    dfs(step - 1, sum + num[step], t + 1);
    vis[step] = 0;
    return ;
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", num + i);
    }
    scanf("%d", &T);
    dfs(n - 1, 0, 0);
    printf("%d\n", cnt);
    return 0;
}


