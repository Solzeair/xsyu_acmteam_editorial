/*************************************************************************
	> File Name: d.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Sat 26 Apr 2025 01:01:16 PM CST
 ************************************************************************/

/*

题意：
给定一个 n 行 m 列的迷宫，每个格子要么为空地 ('.')，要么为障碍 ('*')。
玩家初始位于 (sx, sy)，可以向上下左右移动，但：
  - 向左移动最多 L 步
  - 向右移动最多 R 步
向上、向下移动不受次数限制。
求在这些限制下，从起点出发可以到达的不同格子数（包含起点）。

思路：
这是在二维网格上带有额外“左/右步数”资源限制的可达性问题。
记状态为 (x, y, l, r) —— 当前位置 (x,y)，已向左走 l 步，向右走 r 步。
向上/向下移动时 (l, r) 不变；向左时 l+1；向右时 r+1。
必须满足 l ≤ L 且 r ≤ R 才能继续。
我们对上述状态空间做 BFS：
  - 用队列存储状态 Node{x,y,l,r}。
  - 用 st[x][y] 标记该格子是否已至少被访问过一次。
  - 用 cnt[x][y][0]、cnt[x][y][1] 分别记录到达 (x,y) 时记录的“最小左步数”和“最小右步数”。
如果再次到达同一格子且同时能以更小的 l 和更小的 r 到达，则仍需重新入列探索（这是状态松弛的思想）。

最终，统计首次标记 st[x][y] = 1 时的格子总数，即为所有可达格子数。
*/


#include <iostream>   // 标准输入输出
#include <queue>      // 队列
using namespace std;

int n, m;                        // 迷宫的行数和列数
char g[2005][2005];              // 迷宫地图，'.' 表示空地，'*' 表示障碍
int sx, sy;                      // 起点坐标 (行, 列)
int L, R;                        // 向左最多走 L 步，向右最多走 R 步
int st[2005][2005];              // 访问标记：0 表示未访问，1 表示已访问
int cnt[2005][2005][2];          // 记录到达 (x,y) 时的最小左右移动次数
                                  // cnt[x][y][0] = 最小左移步数
                                  // cnt[x][y][1] = 最小右移步数

// 状态结构：位置 (x,y) 以及已用的左右移动次数 (l, r)
typedef struct Node {
    int x, y, l, r;
} Node;

int res;                         // 可达格子的总数
// 四个方向：右、左、下、上
int dir[4][2] = {
    {0, 1},   // 右
    {0, -1},  // 左
    {1, 0},   // 下
    {-1, 0}   // 上
};

void bfs() {
    queue<Node> q;
    // 从起点开始，左右移动计数都为 0
    q.push({sx, sy, 0, 0});
    res = 1;                     // 起点算一个可达格子

    // 标记起点已访问，替换地图字符防止再次当作空地
    g[sx][sy] = '+';
    st[sx][sy] = 1;
    cnt[sx][sy][0] = 0;          // 起点左移 0 步
    cnt[sx][sy][1] = 0;          // 起点右移 0 步

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        int x = cur.x, y = cur.y;
        int l = cur.l, r = cur.r;

        // 遍历四个方向
        for (int i = 0; i < 4; i++) {
            int dx = x + dir[i][0];
            int dy = y + dir[i][1];

            // 边界检查
            if (dx < 1 || dy < 1 || dx > n || dy > m) continue;
            // 障碍物检查
            if (g[dx][dy] == '*') continue;

            // 计算新的左右移动次数
            // i==1 (向左) 时 l+1；i==0 (向右) 时 r+1
            int nl = l + (i == 1);
            int nr = r + (i == 0);
            // 超出左右移动限制则跳过
            if (nl > L || nr > R) continue;

            // 如果首次访问该格子
            if (st[dx][dy] == 0) {
                st[dx][dy] = 1;
                res++;               // 增加可达格子计数
                cnt[dx][dy][0] = nl; // 记录到达时的左移次数
                cnt[dx][dy][1] = nr; // 记录到达时的右移次数
                q.push({dx, dy, nl, nr});
            }
            // 如果已访问过，但当前路径在左右移动上更优（都更少）
            else if (st[dx][dy] == 1) {
                if (cnt[dx][dy][0] > nl && cnt[dx][dy][1] > nr) {
                    // 更新更优的左右移动次数，并重新入队松弛
                    cnt[dx][dy][0] = nl;
                    cnt[dx][dy][1] = nr;
                    q.push({dx, dy, nl, nr});
                }
            }
        }
    }
}

int main() {
    cin >> n >> m;           // 读入 n, m
    cin >> sx >> sy;         // 读入起点 (sx, sy)
    cin >> L >> R;           // 读入左右移动限制 L, R

    // 读取地图
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> g[i][j];
        }
    }

    bfs();                   // 执行带资源限制的 BFS
    cout << res << endl;     // 输出可达格子总数
    return 0;
}

