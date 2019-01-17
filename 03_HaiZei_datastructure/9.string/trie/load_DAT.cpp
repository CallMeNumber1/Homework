/*************************************************************************
	> File Name: load_DAT.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月06日 星期日 17时26分14秒
 ************************************************************************/

#include <stdio.h>
#include <math.h>
typedef struct DATNode {
    int base, check;
} DATNode;
DATNode trie[500];

void dfs(int ind, int k, char *str) {
    if (trie[ind].check < 0) {
        printf("%s\n", str);
    }
    for (int i = 0; i < 26; i++) {
        int check = fabs(trie[trie[ind].base + i].check);
        // 存在子节点，并且子节点不等于父节点(排除1 1 1根节点这个特殊情况, 不然段错误)
        if (check - ind == 0 && trie[ind].base + i != check) {
            str[k] = i + 'a';
            str[k + 1] = 0;
            dfs(trie[ind].base + i, k + 1, str);
        }
    }
    return ;
}
int main() {
    int a, b, c;
    while (scanf("%d%d%d", &a, &b, &c) != EOF) {
        trie[a].base = b;
        trie[a].check = c;
    } 
    char str[20];
    dfs(1, 0, str);
    return 0;
}
