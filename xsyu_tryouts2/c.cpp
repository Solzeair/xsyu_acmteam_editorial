/*************************************************************************
	> File Name: c.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Thu 24 Apr 2025 05:55:47 PM CST
 ************************************************************************/


/*
思路：
什么情况能赢：鲍勃在第一片或者最后一片荷叶上，且爱丽丝就在他旁边的荷叶上
在这种情况上倒推，因为爱丽丝必然先手，故当两者间隔的荷叶是偶数时，必赢
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int t, n, a, b;
    cin >> t;
    while (t--) {
        cin >> n >> a >> b;
        if (abs(a - b) % 2 == 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
