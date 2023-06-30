using ll = long long;

vector<ll> get_subset_sums(int l, int r, vector<ll> &arr) {
    vector<ll> ans;
    
    int len = r-l+1;
    for (int i = 0; i < (1 << len); i++) {
        ll sum = 0;

        for (int j = 0; j < len; j++) {
            if (i&(1 << j)) {
                sum += arr[l + j];
            }
        }

        ans.push_back(sum);
    }
    
    return ans;
}