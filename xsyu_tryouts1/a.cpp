/*************************************************************************
	> File Name: a.cpp
	> Author: Sakurarry
	> Mail: solzeair@gmail.com
	> Created Time: Sun 20 Apr 2025 09:36:05 AM CST
 ************************************************************************/

#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX 100000
int main() {
    unordered_map<string, int> mp; // 字符串 出现次数
    int n;
    cin >> n;
    string str;
    for (int i = 0; i < n; i++) {
        cin >> str;
        if (mp.find(str) == mp.end()) { // 没找到
            mp[str] = 1;
            cout << "OK" << endl;
        } else { // 已找到
            cout << str << mp[str] << endl;
            mp[str] += 1;
        }
    }
    return 0;
}
