/*************************************************************************
	> File Name: d.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Sat 26 Apr 2025 12:22:06 PM CST
 ************************************************************************/

/*
题意概述
有 𝑛 个格子，初始时只有 𝑚 个格子（位置为 𝑋𝑖 ）上分别有 𝐴𝑖 颗石头。
目标是让每个格子恰好有一颗石头，且只能把第 𝑖 格子的一颗石头移动到第 𝑖+1 格子，一次移动计数为 1。
求最小移动次数，或判断无解。

思路
我们只关心有石头的位置和数量，将它们按位置排序。

维护前缀的“多余石头数” res：表示从开头（第1格）到当前处理位置，已经多出来、可以向右推进的石头数量。

对于相邻两个人有石头的格子（或开头和第一个有石头的位置，及最后一个有石头位置到 𝑛+1的虚拟位置），中间有一段空格，长度为 len = next_x - pos - 1。

要把这段所有格子填满，必须从 res 中拿出 len 颗石头，若 res < len 则无解。

拿出这 len 颗石头往右推的最少步数，就是把当前最“靠左”的那颗多余石头往右推到 pos+1，另一颗推到 pos+2……依次排到 next_x-1。

其移动步数和即等差数列求和

填完这一段后，原位置 next_x 上除了要留一颗石头（目标格子），其余石头都归入 res 便于继续向右推动

在最后，令 X_{m+1}=n+1, A_{m+1}=1 作为哨兵，把最后一段也填完后，若 res 恰好归零，则成功；否则多余石头无法安置，返回无解。
*/

#include <iostream>
#include <algorithm>
using namespace std;

// 使用 long long 以防中间计算溢出
#define int long long
#define MAX_M 200000

// 存储每个有石头的格子：位置 x 和石头数 a
struct Node {
    int x, a;
} arr[MAX_M + 5];

int n, m;

// 按位置从小到大排序
bool cmp(const Node &a, const Node &b) {
    return a.x < b.x;
}

// 等差数列求和：首项 a0，末项 an，共 n 项
int Sn(int a0, int an, int n) {
    return (a0 + an) * n / 2;
}

// 核心检查逻辑，返回最小移动次数或 -1 表示无解
int check() {
    int ans = 0;   // 最终累加的移动次数
    int pos = 0;   // 上一次“有石头格子”的位置（初始视为第0格）
    int res = 0;   // 当前前缀可用的“多余石头数”

    // 在数组末尾添加哨兵：当作第 n+1 格有 1 颗石头，
    // 这样可以把从最后一个真格子到末尾的空格也统一处理
    arr[m + 1].x = n + 1;
    arr[m + 1].a = 1;

    // 遍历所有 m+1 个节点
    for (int i = 1; i <= m + 1; i++) {
        // 这一段长度为 (arr[i].x - pos - 1)
        int len = arr[i].x - pos - 1;

        // 若多余石头不足以填满中间空格，则无解
        if (res < len) return -1;

        // 把这 len 颗石头往右推所需的最少步数
        // 等差首项 res，末项 res-len，共 len+1 项
        ans += Sn(res, res - len, len + 1);

        // 更新：填完这一段后，
        //   用掉了 len 颗石头 → res - len
        //   在位置 x 留 1 颗石头 → + (a - 1)
        res = (res - len) + (arr[i].a - 1);

        // 更新上一次位置
        pos = arr[i].x;
    }

    // 最后如果仍有多余石头，则无法放置，返回 -1
    if (res) return -1;
    return ans;
}

void solve() {
    cin >> n >> m;
    // 读入所有非空格子的位置
    for (int i = 1; i <= m; i++) {
        cin >> arr[i].x;
    }
    // 读入对应位置的石头数量
    for (int i = 1; i <= m; i++) {
        cin >> arr[i].a;
    }

    // 按位置排序，方便按顺序填空
    sort(arr + 1, arr + 1 + m, cmp);
    cout << check() << endl;
    return ;
}

signed main() {
    solve();
    return 0;
}

