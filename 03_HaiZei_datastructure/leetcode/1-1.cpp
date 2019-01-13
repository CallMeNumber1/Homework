/*************************************************************************
	> File Name: 1-1.cpp
	> Author: ChongH
	> Mail: 304451676@qq.com
	> Created Time: 2019年01月13日 星期日 15时59分10秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef struct Data {
    int val, pos;
} Data;
vector<Data> arr;
int main() {

    int n, len, val;
    map<int, int> h;
    cin >> n;
    len = n;
    while (n--) cin >> val, arr.push_back({val, len - n});

    cin >> val;
    for (auto x : arr) {
        if (h.find(val = x.val) == h.end())  {
            h[x.val] = x.pos;
            continue;
        }
        cout << h[val - x.val] << " " << x.pos << endl;
    }
    return 0;
}
