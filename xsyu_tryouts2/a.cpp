/*************************************************************************
	> File Name: a.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Thu 24 Apr 2025 12:13:07 PM CST
 ************************************************************************/

/*
## 题目简述
给定一个 H×W 的网格，每个格子可能是黑色(`#`)、白色(`.`)或未涂色(`?`)。要求将所有 `?` 填成黑或白，使得最终所有黑色格子恰好构成一个连续的矩形区域，其余格子均为白色。


## 解题思路
1. **定位已有黑色格子的边界**
   遍历网格，记录已知黑色(`#`)格子的最小/最大行号和列号，分别记为 `y_l, y_r`（行范围）、`x_l, x_r`（列范围）。至少会有一个黑格。
2. **判断矩形内部**
   对于在边界矩形 `[y_l..y_r]×[x_l..x_r]` 内的每个格子：
   - 如果已有格为白色(`.`)，则不可能将其涂黑，矩形无法成型，答案 `No`。
   - 其他情况（是 `#` 或 `?`）都可染成黑。
3. **边界外格子**
   尽管代码中未显式检查，但矩形外所有格子原本只能是 `.` 或 `?`，无冲突：
   - 若已有 `#` 在矩形外，则前一步求边界时就会把它纳入，保证所有 `#` 都在矩形内。
   - `?` 外部可涂白。
4. **特殊情况**
   - 如果没有任何 `#`（题目保证至少一个），此处可忽略；代码中曾尝试处理 `!black && no_color`，其实也输出了 `Yes`，但题目不会出现这种情况。

整体时间复杂度 O(HW)，空间 O(HW)。
*/

#include <iostream>
#include <climits>
using namespace std;

// 存储网格，行列从 1 开始。
char arr[1005][1005] = {0};

int main() {
    int h, w;
    cin >> h >> w;

    bool flag = true;        // 最终能否构成矩形
    bool black = false;       // 是否存在已知黑格
    bool no_color = false;    // 是否存在未涂色格

    // 初始化边界为极端值
    int x_l = INT_MAX, y_l = INT_MAX;
    int x_r = INT_MIN, y_r = INT_MIN;

    // 读取网格并更新边界
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            char c;
            cin >> c;
            arr[i][j] = c;
            switch (c) {
                case '.':
                    // 白格，无需处理
                    break;
                case '#':
                    // 记录黑格的最小/最大行列
                    y_l = min(y_l, i);
                    y_r = max(y_r, i);
                    x_l = min(x_l, j);
                    x_r = max(x_r, j);
                    black = true;
                    break;
                case '?':
                    // 记录存在未涂色
                    no_color = true;
                    break;
            }
        }
    }

    // 理论上不会出现完全没有 '#' 的情况（题目保证至少一个 '#'）
    // 但代码曾尝试处理这种场景：若既无黑格又有未涂色格，直接输出 Yes
    if (!flag && !black && no_color) {
        cout << "Yes" << endl;
        return 0;
    }

    // 检查边界矩形内部是否有必须为白的格子
    for (int i = y_l; i <= y_r; i++) {
        for (int j = x_l; j <= x_r; j++) {
            if (arr[i][j] == '.') {
                // 矩形内有白格，无法涂黑，失败
                flag = false;
                break;
            }
        }
        if (!flag) break;
    }

    // 输出结果
    if (flag) cout << "Yes" << endl;
    else cout << "No"  << endl;
    return 0;
}



