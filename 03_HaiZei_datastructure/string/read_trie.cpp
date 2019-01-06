/*************************************************************************
	> File Name: Double_Array_Trie.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月06日 星期日 15时15分22秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 确定base值，和有多少个子节点有关系
typedef struct Node {
    int flag;
    struct Node *next[26];
} Node;

typedef struct DATNode {
    int base;
    int check;
} DATNode;


Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    p->flag = 0;
    return p;
}

int insert(Node *node, const char *str) {
    Node *p = node;
    int cnt = 0;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - 'a'] == NULL) {
            p->next[str[i] - 'a'] = getNewNode();
            cnt += 1;
        }
        p = p->next[str[i] - 'a'];
    }
    p->flag = 1;
    return cnt;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < 26; i++) {
        clear(node->next[i]);
    }
    free(node);
    return ;
}

int getBase(Node *node, DATNode *trie) {
    int base = 0, flag = 0;     // 合法
    while (!flag) {
        flag  = 1;
        base += 1;
        for (int i = 0; i < 26; i++) {
            if (node->next[i] == NULL) continue;
            // 这个位置空着
            if (trie[base + i].check == 0) continue;
            flag = 0;
            break;
        }
    }
    return base;
}

// max 节点坐标
int Transform(Node *node, DATNode *trie, int ind) {
    if (ind == 1) trie[ind].check = 1;
    // 取反
    if (node->flag) trie[ind].check = -trie[ind].check;
    trie[ind].base = getBase(node, trie);
    for (int i = 0; i < 26; i++) {
        // 当前节点没有第i孩子
        if (node->next[i] == NULL) continue;
        trie[trie[ind].base + i].check = ind;
    }
    int ret = ind;
    for (int i = 0; i < 26; i++) {
        if (node->next[i] == NULL) continue;
        int temp = Transform(node->next[i], trie, trie[ind].base + i);
        if (temp > ret) ret = temp;
    }
    return ret;
}


int search(DATNode *trie, const char *str) {
    int p = 1;  // 根节点
    for (int i = 0; str[i]; i++) {
        int delta = str[i] - 'a';
        int check = abs(trie[trie[p].base + delta].check);
        if (check - p) return 0;
        p = trie[p].base + delta;
    }
    return trie[p].check < 0;
}

void Output(DATNode *trie, int ind) {
    
}




int main() {
    DATNode *dat = (DATNode *)malloc(sizeof(DATNode) * 200);
    int ind;
    while (scanf("%d", &ind) != EOF) {
        scanf("%d%d", &dat[ind].base, &dat[ind].check);
    }
    //printf("%d\n", ind);
    char strs[40][20] = {0};
    int cnt = 0, k = 0;
    for (int i = 1; i <= ind; i++) {
        for (int j = 0; j < 26; j++) {
            int check = dat[dat[i].base + i].check;
            // 如果不是ind的孩子
            if (check != abs(ind)) continue;
            if (check < 0) {
                strs[cnt][k] = j + 'a';
                // 独立成词，cnt++去构造下一个词
                cnt++;
                k = 0;
            } else {
                strs[cnt][k] = j + 'a';
                k++;
            }
            
        }
    }  
    printf("cnt:%d\n", cnt);
   return 0;
}
