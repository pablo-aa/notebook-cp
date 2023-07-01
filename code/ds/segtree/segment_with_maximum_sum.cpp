// Description:
// Query - get sum of segment that is maximum among all segments
// E.g 
// Array: 5 -4 4 3 -5
// Maximum segment sum: 8 because 5 + (-4) + 4 = 8
// Update - update element at position id to a value val

// Problem:
// https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A

// Complexity:
// O(log n) for both query and update

// How to use:
// Segtree seg = Segtree(n);
// seg.build(v);

// Notes
// The maximum segment sum can be a negative number
// In that case, taking zero elements is the best choice
// So we need to take the maximum between 0 and the query
// max(0LL, seg.query(0, n).max_seg)

using ll = long long;

typedef ll ftype_node;

struct Node {
    ftype_node max_seg;
    ftype_node pref;
    ftype_node suf;
    ftype_node sum;
    
    Node(ftype_node max_seg, ftype_node pref, ftype_node suf, ftype_node sum) : max_seg(max_seg), pref(pref), suf(suf), sum(sum) {};
};

typedef Node ftype;

struct Segtree {
    vector<ftype> seg;
    int n;
    const ftype NEUTRAL = Node(0, 0, 0, 0);
 
    Segtree(int n) {
        int sz = 1;
        // potencia de dois mais proxima
        while (sz < n) sz *= 2;
        this->n = sz;
 
        // numero de nos da seg
        seg.assign(2*sz, NEUTRAL);
    }

    ftype f(ftype a, ftype b) {
        ftype_node max_seg = max({a.max_seg, b.max_seg, a.suf + b.pref});
        ftype_node pref = max(a.pref, a.sum + b.pref);
        ftype_node suf = max(b.suf, b.sum + a.suf);
        ftype_node sum = a.sum + b.sum;
        
        return Node(max_seg, pref, suf, sum);
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
            seg[pos] = Node(val, val, val, val);
 
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
            // se a posição existir no array original
            // seg tamanho potencia de dois
            if (ini < (int)v.size()) {
                seg[pos] = Node(v[ini], v[ini], v[ini], v[ini]);
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
            cout << e.max_seg << ' ' << e.pref << ' ' << e.suf << ' ' << e.sum << '\n';
        }
        cout << '\n';
    }
};