/*************************************************************************
	> File Name: 235.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月25日 星期四 20时33分30秒
 ************************************************************************/

#include<iostream>
using namespace std;

int guang(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q, struct TreeNode **result) {
    if (root == NULL) return 0;
    int ret = (root == p || root == q);
    ret += guang(root->left, p, q, result);
    if (ret == 2 && *result == NULL) *result = root;
    ret += guang(root->right, p, q, result);
    if (ret == 2 && *result == NULL) *result = root;
    return ret;
}

struct TreeNode *lowestCommonAncestor(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q) {
    struct TreeNode *result = NULL;
    guang(root, p, q, &result);
    return result;
}


