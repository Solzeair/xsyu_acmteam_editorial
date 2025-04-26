/*************************************************************************
	> File Name: h.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Thu 24 Apr 2025 05:35:55 PM CST
 ************************************************************************/

/*
思路
如果 s 中包含 m 或 w，则不可能生成。

对于连续的 u 串或 n 串，任意相邻的两个 u（或 n）也可以组合来源于一个 w（或 m）。
打表得知（连续u的数量 n = 2, 3，4 ... ）符合斐波那契数列 2，3，5 ...
*/

#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 1000005
typedef long long ll;

const int MOD = 1000000007;
char s[MAXN];
ll dp[MAXN];

int main() {
    cin >> s;
    int n = strlen(s);

    dp[0] = 1; // 初始化边界值

    for (int i = 1; i <= n; i++) { // 特殊情况
        char c = s[i - 1];
        if (c == 'm' || c == 'w') {
            printf("0\n");
            return 0;
        }
        
        // 若连续则斐波那契，否则传递原值
        if (i >= 2 && s[i - 2] == 'u' && s[i - 1] == 'u') {
            dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
        } else if (i >= 2 && s[i - 2] == 'n' && s[i - 1] == 'n') {
            dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
        } else dp[i] = dp[i - 1];
    }

    cout << dp[n];
    return 0;
}
