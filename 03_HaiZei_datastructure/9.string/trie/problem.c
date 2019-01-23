/*************************************************************************
	> File Name: problem.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月23日 星期三 21时32分33秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
const int N = 100010;
const int SIZE = 2;
const char BASE = 'a';

typedef struct TrieNode {
    int flag;
    struct TrieNode *next[2];
} TrieNode, *Trie;
typedef struct Node {
    int key, freq;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key, int freq) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->freq = freq;
    p->lchild = p->rchild = NULL;
    return p;
}

int swap_node(Node **p, Node **q) {
    Node *temp = *p;
    *p = *q;
    *q = temp;
    return 1;
}

Node *build_haffman(Node **arr, int n) {

    printf("build\n");
    Node INIT_NODE = {0, INT32_MAX, NULL, NULL};
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 2; j++) {
            if (arr[j]->freq < arr[n - i - 1]->freq) {
                swap_node(arr + j, arr + n - i - 1);
            }
            if (arr[j]->freq < arr[n - i - 2]->freq) {
                swap_node(arr + j, arr + n - i - 2);
            }
        }
        Node *temp = getNewNode(0, arr[n - i - 1]->freq + arr[n - i - 2]->freq);
        temp->lchild = arr[n - i - 1];
        temp->rchild = arr[n - i - 2];
        arr[n - i - 2] = temp;
    }
    printf("build\n");
    return arr[0];
}

void extract_code(Node *root, char (*code)[50], int k, char *buff) {
    buff[k] = 0;
    if (root->key) {
        strcpy(code[root->key], buff);
        return ;
    }
    buff[k] = '0';
    extract_code(root->lchild, code, k + 1, buff);
    buff[k] = '1';
    extract_code(root->rchild, code, k + 1, buff);
    return ;
}
TrieNode* new_node() {
	TrieNode *p = (TrieNode *)calloc(1, sizeof(TrieNode));
    return p;
}

void clear(TrieNode *root) {
    if (!root) return ;
    for (int i = 0; i < SIZE; i++) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}

void insert(TrieNode *root, char *str, char (*code)[50]) {
    TrieNode *p = root;
    for (int i = 0; str[i]; i++) {
        for (int j = 0; code[str[i]][j]; j++) {
            int bit = (code[str[i]][j] - '0');
            if (p->next[bit] == NULL) p->next[bit] = new_node();
            p = p->next[bit];
        }
        p->flag = 1;
    }

    return ;

}

int search(TrieNode *root) {
    if (root == NULL) return 0;
    TrieNode *p = root;
    int ret = 0;
	for (int i = 0; i < SIZE; i++) {
        if (p->next[i] == NULL) continue;
        if (p->next[i]->flag == 1) ret += 1;
    	ret += search(p->next[i]);
    }
    return ret;

}

int main() {
    int num[256] = {0}, vis[256] = {0};
    int n;                                  // 编码字符数量
    char s[N];
    scanf("%s", s);
    for (int i = 0; s[i]; i++) {          // 统计字符出现的频次
        num[s[i]]++;
        if (num[s[i]] == 1) n++;
    }
    printf("n = %d\n", n);
    Node **arr = (Node **)malloc(sizeof(Node *) * n);
    Node *root_haffuman;
    for (int i = 0; s[i]; i++) {
        if (num[s[i]] == 0 || vis[s[i]]) continue;
        vis[s[i]] = 1;
        printf("%c %d\n", s[i], num[s[i]]);
        arr[i] = getNewNode(s[i], num[s[i]]);
    }
    root_haffuman = build_haffman(arr, n);
    printf("build!\n");
    char code[256][50] = {0}, buff[50];
    extract_code(root_haffuman, code, 0, buff);
    for (int i = 0; i < 256; i++) {
        if (code[i][0] == 0) continue;
        printf("%c : %s\n", i, code[i]);
    }

    TrieNode *root = new_node();
    for (int i = 0; i < strlen(s); i++) {
        insert(root, s + i, code);
    }
    // -1 : 减去根节点
	int ans = search(root);
    printf("%d\n", ans);
    return 0;
}
