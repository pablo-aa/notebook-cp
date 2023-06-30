using ll = long long;

ll fexp(ll base, ll exp, ll m) {
    ll ans = 1;
    base %= m;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            ans = (ans * base) % m;
        }
 
        base = (base * base) % m;
        exp /= 2;
    }
 
    return ans;
}