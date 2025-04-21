/*************************************************************************
	> File Name: g.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Mon 21 Apr 2025 09:01:35 PM CST
 ************************************************************************/

#include <iostream>
#include <queue>
using namespace std;
#define MAX_N 300000
#define mk make_pair

const int mod = 998244353;

struct Node {
    int to, nxt;
} e[MAX_N + 5]; // 单向边
int head[MAX_N + 5], tot = 0;

void add(int u, int v) { // u -> v
    tot += 1;
    e[tot].nxt = head[u];
    e[tot].to = v;
    head[u] = tot;
    return ;
}

int n;
int dp[MAX_N + 5]; // 到达当前点的方案数
int f[MAX_N + 5]; // 步长为 d 的方案数
int ans;

void bfs(int x) {
    queue<pair<int, pair<int, int>>> q; // u, {父节点, 步长}
    dp[1] = 1;
    f[1] = 1;
    for (int i = head[1]; i; i = e[i].nxt) q.push(mk(e[i].to, mk(0, 2)));
    while (!q.empty()) {
        auto temp = q.front();
        q.pop();
        int u = temp.first;
        int fa = temp.second.first;
        int d = temp.second.second;
        dp[u] = ((f[d - 1] - dp[fa]) % mod + mod) % mod;
        f[d] = (f[d] + dp[u]) % mod;
        for (int i = head[u]; i; i = e[i].nxt) q.push(mk(e[i].to, mk(u, d + 1)));
    }
    for (int i = 1; i <= n; i++) ans = (ans + dp[i]) % mod; // 避免负数
}

void solve() {
    cin >> n;
    tot = 0;
    for (int i = 1; i <= n; i++) head[i] = 0, dp[i] = 0, f[i] = 0;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        add(p, i);
    }
    ans = 0;
    bfs(1);
    cout << ans << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
