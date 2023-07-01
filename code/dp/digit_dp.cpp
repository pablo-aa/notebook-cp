// Digit DP 1: https://atcoder.jp/contests/dp/tasks/dp_s
//
// find the number of integers between 1 and K (inclusive)
// where the sum of digits in base ten is a multiple of D

#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9+7;

string k;
int d;

int tb[10010][110][2];

int dp(int pos, int sum, bool under) {
    if (pos >= k.size()) return sum == 0;
    
    int& mem = tb[pos][sum][under];
    if (mem != -1) return mem;
    mem = 0;
    
    int limit = 9;
    if (!under) limit = k[pos] - '0';
    
    for (int digit = 0; digit <= limit; digit++) {
        mem += dp(pos+1, (sum + digit) % d, under | (digit < limit));
        mem %= MOD;
    }
    
    return mem;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> k >> d;
    
    memset(tb, -1, sizeof(tb));
    
    cout << (dp(0, 0, false) - 1 + MOD) % MOD << '\n';
    
    return 0;
}