/*************************************************************************
	> File Name: c.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Sun 20 Apr 2025 01:24:05 PM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 200000

int fa[2 * MAX_N + 5];
void init(int n) {
    for (int i = 1; i <= 2 * n; i++) fa[i] = i;
}

int find(int x) {
    return fa[x] = (fa[x] == x ? x : find(fa[x]));
}

void merge(int a, int b) {
    int aa = find(a), bb = find(b);
    if (aa == bb) return ;
    fa[aa] = bb;
    return ;
}

void solve() {
    int n;
    cin >> n;
    
    // 初始化
    int num[MAX_N + 5] = {0};
    vector<pair<int, int>> arr;
    init(n); 
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        num[a] += 1;
        num[b] += 1;
        arr.push_back({a, b});
    }

    // 因为单个集合中有 n/2 个牌，且集合中的数字不重复
    // 故单个集合中的数字必为 1~n 的整数全集
    // 两个集合的数字加起来，1~n 的每个数字必然出现两次
    for (int i = 1; i <= n; i++) {
        if (num[i] == 2) continue;
        cout << "NO" << endl;
        return ;
    }
    
    // 并查集
    for (int i = 0; i < n; i++) {
        int u = arr[i].first;
        int v = arr[i].second;
        // 集合中出现重复
        if (find(u) == find(v)) {
            cout << "NO" << endl;
            return ;
        }
        // 否则，连接
        merge(u, v + n);
        merge(v, u + n);
    }
    cout << "YES" << endl;
    return ;
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
