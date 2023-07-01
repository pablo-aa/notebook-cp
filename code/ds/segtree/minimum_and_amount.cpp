// Description:
// Query - get minimum element in a range (l, r) inclusive
// and also the number of times it appears in that range
// Update - update element at position id to a value val

// Problem:
// https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C

// Complexity:
// O(log n) for both query and update

// How to use:
// Segtree seg = Segtree(n);
// seg.build(v);

#define pii pair<int, int>
#define mp make_pair
#define ff first
#define ss second

const int INF = 1e9+17;

typedef pii ftype;

struct Segtree {
    vector<ftype> seg;
    int n;
    const ftype NEUTRAL = mp(INF, 0);
 
    Segtree(int n) {
        int sz = 1;
        while (sz < n) sz *= 2;
        this->n = sz;
 
        seg.assign(2*sz, NEUTRAL);
    }

    ftype f(ftype a, ftype b) {
        if (a.ff < b.ff) return a;
        if (b.ff < a.ff) return b;
        
        return mp(a.ff, a.ss + b.ss);
    }
 
    ftype query(int pos, int ini, int fim, int p, int q) {
        if (ini >= p && fim <= q) {
            return seg[pos];
        }
 
        if (q < ini || p > fim) {
            return NEUTRAL;
        }
 
        int e = 2*pos + 1;
        int d = 2*pos + 2;
        int m = ini + (fim - ini) / 2;
 
        return f(query(e, ini, m, p, q), query(d, m + 1, fim, p, q));
    }
 
    void update(int pos, int ini, int fim, int id, int val) {
        if (ini > id || fim < id) {
            return;
        }
 
        if (ini == id && fim == id) {
            seg[pos] = mp(val, 1);
 
            return;
        }
 
        int e = 2*pos + 1;
        int d = 2*pos + 2;
        int m = ini + (fim - ini) / 2;
 
        update(e, ini, m, id, val);
        update(d, m + 1, fim, id, val);
 
        seg[pos] = f(seg[e], seg[d]);
    }
 
    void build(int pos, int ini, int fim, vector<int> &v) {
        if (ini == fim) {
            if (ini < (int)v.size()) {
                seg[pos] = mp(v[ini], 1);
            }
            return;
        }
 
        int e = 2*pos + 1;
        int d = 2*pos + 2;
        int m = ini + (fim - ini) / 2;
 
        build(e, ini, m, v);
        build(d, m + 1, fim, v);
 
        seg[pos] = f(seg[e], seg[d]);
    }
 
    ftype query(int p, int q) {
        return query(0, 0, n - 1, p, q);
    }
 
    void update(int id, int val) {
        update(0, 0, n - 1, id, val);
    }
 
    void build(vector<int> &v) {
        build(0, 0, n - 1, v);
    }
 
    void debug() {
        for (auto e : seg) {
            cout << e.ff << ' ' << e.ss << '\n';
        }
        cout << '\n';
    }
};