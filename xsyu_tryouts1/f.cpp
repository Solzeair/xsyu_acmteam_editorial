/*************************************************************************
	> File Name: f.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Mon 21 Apr 2025 09:35:42 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define MAX_N 20

int n;
int a[MAX_N + 5];
int minmaxval = INT32_MAX;
// dfs
void f(int x, int sum1, int sum2) {
    if(x == n) {
        int y = max(sum1, sum2);
        minmaxval = min(minmaxval, y);
        return ;
    }
    f(x + 1, sum1 + a[x], sum2);
    f(x + 1, sum1, sum2 + a[x]);
    return ;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    f(0, 0, 0);
    cout << minmaxval << endl;
    return 0;
}
