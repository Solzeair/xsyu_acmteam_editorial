/*************************************************************************
	> File Name: e.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Mon 21 Apr 2025 09:42:23 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

ll a[105], n, h;
int main() {
    int T; 
    cin >> T;
    while (T--) {
        cin >> n >> h;
        for (int i = 1; i <= n; i++) cin >> a[i];
        ll l = 1, r = 1e18;
        while (l <= r) {
            ll mid = (l + r) >> 1, ans = mid;
            for (int i = 1; i < n; i++) 
                ans += min(mid, a[i + 1] - a[i]);
            if (ans < h) l = mid + 1;
            else r = mid - 1;
        }
        cout << r + 1 << endl;
    }
    return 0;
}
