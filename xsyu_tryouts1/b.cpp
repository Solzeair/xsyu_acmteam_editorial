/*************************************************************************
	> File Name: b.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Sun 20 Apr 2025 10:23:21 AM CST
 ************************************************************************/

#include <iostream>
using namespace std;

char arrn[55][55];
char arrm[55][55];

// 二选一
// 循环
bool match(int si, int sj, int m) {
    for (int dx = 0; dx < m; dx++) {
        for (int dy = 0; dy < m; dy++) {
            if (arrn[si + dx][sj + dy] != arrm[dx + 1][dy + 1])
                return false;
        }
    }
    return true;
}

// 递归
bool dfs(int x, int y, int si, int sj, int m) {
    if (arrn[si + x - 1][sj + y - 1] != arrm[x][y]) return false;
    if (x == m && y == m) return true;
    int nx = x, ny = y + 1;
    if (ny > m) {
        nx = x + 1;
        ny = 1;
    }
    return dfs(nx, ny, si, sj, m);
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> arrn[i][j];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            cin >> arrm[i][j];

    for (int i = 1; i + m - 1 <= n; i++) {
        for (int j = 1; j + m - 1 <= n; j++) {
            if (match(i, j, m)) { // dfs修改if判断条件 dfs(1, 1, i, j, m)
                cout << i << " " << j << endl;
                return 0;
            }
        }
    }
    return 0;
}

