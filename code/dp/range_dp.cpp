// Range DP 1: https://codeforces.com/problemset/problem/1132/F
// 
// You may apply some operations to this string
// in one operation you can delete some contiguous substring of this string
// if all letters in the substring you delete are equal
// calculate the minimum number of operations to delete the whole string s

#include <bits/stdc++.h>

using namespace std;

const int MAX = 510;

int n, tb[MAX][MAX];
string s;

int dp(int left, int right) {
    if (left > right) return 0;

    int& mem = tb[left][right];
    if (mem != -1) return mem;
    
    mem = 1 + dp(left+1, right); // gastar uma operação arrumando só o cara atual
    for (int i = left+1; i <= right; i++) {
        if (s[left] == s[i]) {
            mem = min(mem, dp(left+1, i-1) + dp(i, right));
        }
    }

    return mem;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> s;
    memset(tb, -1, sizeof(tb));
    cout << dp(0, n-1) << '\n';

    return 0;
}