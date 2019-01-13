/*************************************************************************
	> File Name: 1.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月13日 星期日 15时54分19秒
 ************************************************************************/



// 哈希做法
// vector版

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
#define MAX_N 500

typedef struct Data {
    int val, pos;
} Data;

vector<Data> arr;

bool cmp(Data &a, Data &b) {
    return a.val < b.val;
}
int main() {

    int n, len, val;
    cin >> n;
    len = n;
    while (n--) cin >> val, arr.push_back({val, len - n});
    sort(arr.begin(), arr.end(), cmp);
    int i = 0, j = arr.size() - 1;
    cin >> val;
    while (arr[i].val + arr[j].val != val) {
        if (arr[i].val + arr[j].val < val) ++i;
        else --j;
    }
    if (arr[i].pos > arr[j].pos) swap(arr[i], arr[j]);
    cout << arr[i].pos << " " << arr[j].pos << endl;

    return 0;
}
