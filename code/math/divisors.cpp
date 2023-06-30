vector<ll> divisors(ll n) {
    vector<ll> ans;

    for (ll i = 1; i*i <= n; i++) {
        if (n%i == 0) {
            ll value = n/i;
            
            ans.push_back(i);
            if (value != i) {
                ans.push_back(value);
            }
        }
    }
    
    return ans;
}