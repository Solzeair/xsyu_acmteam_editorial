/*************************************************************************
	> File Name: d.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Sun 20 Apr 2025 02:19:52 PM CST
 ************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

// 线性筛
#define MAX_N 1000000
int prime[MAX_N + 5] = {0};
int notprime[MAX_N + 5] = {0, 1};
void init_prime() {
    for (int i = 2; i <= MAX_N; i++) {
        if (!notprime[i]) prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0]; j++) {
            if (prime[j] * i > MAX_N) break;
            notprime[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    return ;
}

int main() {
    int n;
    cin >> n;
    init_prime(); // 初始化素数数组
    long long arr[100005] = {0};
    for (int i = 0; i < n; i++) cin >> arr[i];
    // 除 1和数字本身，只能是平方根为因数 
    for (int i = 0; i < n; i++) {
        long long a = floor(sqrt(arr[i]));
        if (a * a != arr[i]) { 
            cout << "NO" << endl;
            continue;
        }
        if (notprime[a]) { 
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
    }
    return 0;
}
