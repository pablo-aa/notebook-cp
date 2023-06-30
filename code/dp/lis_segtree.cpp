#include <bits/stdc++.h>
 
using namespace std;
 
const int MAX = 2e5+17;
 
struct segTree {
    int size;
    vector<int> tree;
 
    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size, 0LL);
    }
 
    int merge(int a, int b) {
        return max(a, b);
    }
 
    void build(vector<int> &arr, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)arr.size())
                tree[x] = arr[lx];
            
            return;
        }
        
        int m = (lx + rx) / 2;
        build(arr, 2 * x + 1, lx, m);
        build(arr, 2 * x + 2, m, rx);
 
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
 
    void build(vector<int> &arr) {
        build(arr, 0, 0, size);
    }
 
    void update(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = v;
            return;
        }
 
        int m = (lx + rx) / 2;
        if (i < m) {
            update(i, v, 2 * x + 1, lx, m);
        } else {
            update(i, v, 2 * x + 2, m, rx);
        }
 
        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
 
    void update(int i, int v) {
        update(i, v, 0, 0, size);
    }
 
    int query(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return 0;
        if (lx >= l && rx <= r) return tree[x];
 
        int m = (lx + rx) / 2;
        int s1 = query(l, r, 2 * x + 1, lx, m);
        int s2 = query(l, r, 2 * x + 2, m, rx);
 
        return merge(s1, s2);
    }
 
    int query(int l, int r) {
        return query(l, r, 0, 0, size);
    }
};
 
 
int main() {
	ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, arr[MAX], aux[MAX]; cin >> n;
    for (int i = 0; i < n; i++) {
    	cin >> arr[i];
 
    	aux[i] = arr[i];
    }
 
    sort(aux, aux+n);
 
    segTree st;
    st.init(n);
 
    int ans = 0;
    for (int i = 0; i < n; i++) {
    	int it = lower_bound(aux, aux+n, arr[i]) - aux;
    	int lis = st.query(0, it) + 1;
 
    	st.update(it, lis);
 
    	ans = max(ans, lis);
    }
 
    cout << ans << '\n';
 
	return 0;
}