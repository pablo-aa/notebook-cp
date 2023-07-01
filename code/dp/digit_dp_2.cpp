// Digit DP 2: https://cses.fi/problemset/task/2220
//
// Number of integers between a and b
// where no two adjacents digits are the same

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
 
const int MAX = 20; // 10^18
 
ll tb[MAX][MAX][2][2];
 
ll dp(string& number, int pos, int last_digit, bool under, bool started) {
    if (pos >= (int)number.size()) {
        return 1;
    }
 
    ll& mem = tb[pos][last_digit][under][started];
    if (mem != -1) return mem;
    mem = 0;
 
    int limit = 9;
    if (!under) limit = number[pos] - '0';
 
    for (int digit = 0; digit <= limit; digit++) {
        if (started && digit == last_digit) continue;
 
        bool is_under = under || (digit < limit);
        bool is_started = started || (digit != 0);
 
        mem += dp(number, pos+1, digit, is_under, is_started);
    }
 
    return mem;
}
 
ll solve(ll ubound) {
    memset(tb, -1, sizeof(tb));
    string number = to_string(ubound);
    return dp(number, 0, 10, 0, 0);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll a, b; cin >> a >> b;
    cout << solve(b) - solve(a-1) << '\n';
    
    return 0;
}