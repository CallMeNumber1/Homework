/*************************************************************************
	> File Name: raddix.c
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2018年10月21日 星期日 11时00分20秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void raddix_sort(int *num, int n) {
    int *temp = (int *)malloc(sizeof(sizeof(int) * n));
    int cnt[65537] = {0};   //2^16
    // 对后16位排序
    for (int i = 0; i < n; i++) cnt[(num[i] & 0xffff) + 1]++;     //0xffff = 65536
    for (int i = 1; i < 65536; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) temp[cnt[(num[i] & 0xffff)]++] = num[i];
    // 对前16位排序
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++) cnt[((temp[i] >> 16) & 0xffff) + 1]++;
    for (int i = 1; i < 65536; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) num[cnt[(temp[i] >> 16) &  0xffff]++] = temp[i];
    memset(cnt, 0, sizeof(cnt));

}
void output(int *num, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
    return ;
}
int main() {
    srand(time(0));
    int arr[100];
    for (int i = 0; i <100; i++) arr[i] = rand() % 100;
    raddix_sort(arr, 100);
    output(arr, 100);
    return 0;
}
