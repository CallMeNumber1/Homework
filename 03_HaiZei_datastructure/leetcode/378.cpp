/*************************************************************************
	> File Name: 378.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月19日 星期六 10时51分13秒
 ************************************************************************/


#include <stdio.h>

// 二分
// 前0后1
int kthSmallest(int matrix[][100], int row, int col, int k) {
    int head = matrix[0][0], tail = matrix[row - 1][col - 1], mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        int cnt = 0, j = col - 1;
        // 寻找一个阶梯型
        // cnt每次累加大于mid值的个数
        for (int i = 0; i < row; i++) {
            while (j >= 0 && matrix[i][j] > mid) j--;
            cnt += (j + 1);
        }
        if (cnt < k) head = mid + 1;
        else tail = mid;
    }
    return head;

}



int main() {
    int matrix[100][100];
    int n, k;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    scanf("%d", &k);
    //printf("%d %d\n", n, k);
   
    printf("%d\n", kthSmallest(matrix, n, n, k));
    return 0;
}
