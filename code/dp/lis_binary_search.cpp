int lis(vector<int> arr) {
    vector<int> dp;
    
    for (auto e : arr) {
        int pos = lower_bound(dp.begin(), dp.end(), e) - dp.begin();
        
        if (pos == (int)dp.size()) {
            dp.push_back(e);
        } else {
            dp[pos] = e;
        }
    }
    
    return (int)dp.size();
}