/*************************************************************************
	> File Name: 2.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月13日 星期日 18时08分15秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main() {
    int n, val;
    cin >> n;
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        cin >> val;
        val = (val < 0 || val > n ? 0 : val);
        // 所有非法值换成了0
        arr.push_back(val);
    }
    for (int i = 0; i < n; i++) {
        // 不是0且不是应该存储的值，就放到应该存的位置
        while (arr[i] != 0 && arr[i] != i + 1) {
            swap(arr[i], arr[arr[i] - 1]);
        }
    } 
    
}
