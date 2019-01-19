/*************************************************************************
	> File Name: 1-2.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月19日 星期六 11时41分09秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

/*
 *　杨氏矩阵做法
 *  要求一维数组是递增的情况
 *  否则会出现下标不正确的情况（排序后下标变化）
 *  这时可以将下标封装到结构体后排序，但好麻烦。。。
 *  代码如下
 */
typedef struct Node {
    int val;
    int pos;
} Node;
int cmp(const void *a, const void *b) {
    Node *aa = (Node *)a;
    Node *bb = (Node *)b;
    return (((aa->val) > (bb->val))? 1 : -1);
}
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return ;
}
int *twoSum(int *nums, int size, int target) {
    // 因为答案要求的是下标，将下标封装到结构体，按值排序
    Node *nodes = (Node *)malloc(sizeof(Node) * size);
    for (int i = 0; i < size; i++) {
        nodes[i].val = nums[i];
        nodes[i].pos = i;
    }
    qsort(nodes, size, sizeof(Node), cmp);
    int *ret = (int *)malloc(sizeof(int) * 2);
    int j = size - 1;
    for (int i = 0; i < size; i++) {
        while (j >= 0 && nodes[j].val + nodes[i].val > target) j--;
        if (nodes[j].val + nodes[i].val == target) {
            ret[0] = nodes[i].pos;
            ret[1] = nodes[j].pos;
            break;
        }
    }
    if (ret[0] > ret[1]) swap(&ret[0], &ret[1]);
    return ret;
}


int main() {
    
    int n, nums[100], target;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", nums + i);
    }
    scanf("%d", &target);
    twoSum(nums, n, target);
    return 0;
}
