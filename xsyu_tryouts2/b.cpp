/*************************************************************************
	> File Name: b.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Thu 24 Apr 2025 03:38:43 PM CST
 ************************************************************************/

/*
题意：
有 n 堆石子，我们可以从第三堆开始，每次拿出 3 * di 枚石子（0 <= di <= ai/3), 将其中 di 枚放入第 d-1 堆中，将 2*di 枚石子放入第 i-2 堆石子中。问最少的那堆石子最多有几枚

想法：二分
由于方便计算 di 所以我们可以在读入的时候将整个数组反过来。对于每个 mid 我们将这 n 堆石子所能取到的最大的 di 统计下来。并且在统计的过程中记录方案是否合法。

对于每个 di 一定要对它取个 min(di, ai/3)。
第一堆和第二堆没有 di。
*/


#include<iostream>
using namespace std;

#define MAX_N 200000

int a[MAX_N + 5]; // 原始堆
int b[MAX_N + 5]; // 分出 di 后的堆

bool check(int x, int n) {
    for (int i = 1; i <= n; i++) b[i] = a[i];
    for (int i = n; i >= 3; i--) {
        if (b[i] >= x) {
            int d = min(a[i] / 3, (b[i] - x) / 3); // 取最小 di
            b[i - 1] += d;
            b[i - 2] += 2 * d;
        } else {
            return false; // 不满足最小堆的最大值是 x
        }
    }
    if (b[1] < x || b[2] < x) return false; // 易忘
    return true;
}
// 二分查找 最小堆的最大值 mid
int find(int n, int r) {
    int l = 0, mid;
    while (l < r) {
        mid = (l + r + 1) / 2;
        if (check(mid, n)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;   
}

void solve() {
    int n;
    cin >> n;
    int r = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        r = max(r, a[i]); // 二分边界值
    }
    cout << find(n, r) << endl;
    return ;
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
