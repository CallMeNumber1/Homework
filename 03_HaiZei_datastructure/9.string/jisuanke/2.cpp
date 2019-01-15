/*************************************************************************
	> File Name: 2.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月14日 星期一 18时19分38秒
 ************************************************************************/

/*
// 本题思路出错 按字典序打印并不是最小的
    正确思路：
    将最长的字符串放到最后打印，这样得出的方案数是最小的
    因此在插入字典树的时候统计单词中不重复字符的count,(例如add,apple)
    插入时count加到了7。
    最后结果为2 * count - max_str_len + n
    其中2 * count代表每个字符要输入且删去，n代表打印的次数
    减去的max_str_len，是因为最后一行为最长的单词，不必删除，而计算
    2*count时算在内，因此减去
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 26
#define BEGIN 'a'

typedef struct Node {
    struct Node *next[BASE];
    int flag;
    char *str;
} Node;

Node *getNewNode() {
    Node *p = (Node *)calloc(1, sizeof(Node));
    return p;
}

void insert(Node *root, char *str) {
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BEGIN] == NULL) p->next[str[i] - BEGIN] = getNewNode();
        p = p->next[str[i] - BEGIN];
    }
    p->flag = 1;
    p->str = strdup(str);
    return ;
}

int search(Node *root, char *str) {
    
}



void clear(Node *root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}

char ans[10005][55] = {0};
int cnt = 0;
// 字典树的中序遍历(仿二叉树) 可实现按字典序输出
void inorder(Node *root) {
    if (root == NULL) return ;
    if (root->flag == 1) {
        strcpy(ans[cnt++], root->str);
    }
    for (int i = 0; i < BASE; i++) {
        inorder(root->next[i]);
    }
    return ;
}

int find_common(char *str1, char *str2) {
    int len1 = strlen(str1), len2 = strlen(str2);
    int i = 0, j = 0, ret = 0;
    while (i < len1 && j < len2) {
        if (str1[i] == str2[j]) {
            ret++, i++, j++;
        } else break;
    }
    return ret;
}
// 问题：按字典序读出时有时并不是最短的
// 比如：abb accle  
int main() {
    int n;
    char str[55];
    while (scanf("%d", &n) != EOF) {
        Node *root = getNewNode();
        memset(ans, 0, sizeof(ans));
        cnt = 0;

        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            insert(root, str);
        }
        int res = 0, del_num = 0, common = 0;
        inorder(root);
       
        // 每一个字符串要按的按钮次数为：自身长度，del次数，print次数
        for (int i = 0; i < cnt; i++) {
            // printf("%s\n", ans[i]);
            // 自身长度减去上次已经输入的（没有删减完的字符）
            int len = strlen(ans[i]) - common;
            if (i != cnt - 1) {
                common = find_common(ans[i], ans[i + 1]);
                del_num = len - common;
                res += (len + del_num + 1);
            } else res += (len + 1);
            // printf("%d\n", res);
        }
        printf("%d\n", res);

    }
    /*
    // 插入字典树后进行层序遍历, 实现的是按长度递增输出单词，而非字典序
    Node **queue = (Node **)calloc(10000, sizeof(Node *));
    int head = 0, tail = 0;
    queue[tail++] = root;
    while (head < tail) {
        Node *p = queue[head++];
        for (int i = 0; i < BASE; i++) {
            if (p->next[i] == NULL) continue;
            queue[tail++] = p->next[i];
            if (p->next[i]->flag == 1) {
                // 注意！！是p->next[i]指向的，不是p指向的
                printf("%s\n", p->next[i]->str);
            }   
        }
    }
    */
    return 0;

}


