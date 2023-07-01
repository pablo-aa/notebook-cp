// Description:
// Indexed at one

// When the indexes of the nodes are too big to be stored in an array
// and the queries need to be answered online so we can't sort the nodes and compress them
// we create nodes only when they are needed so there'll be (Q*log(MAX)) nodes
// where Q is the number of queries and MAX is the maximum index a node can assume

// Query - get sum of elements from range (l, r) inclusive
// Update - update element at position id to a value val

// Problem:
// https://oj.uz/problem/view/IZhO12_apple

// Complexity:
// O(log n) for both query and update

// How to use:
// MAX is the maximum index a node can assume
// Create a default null node
// Create a node to be the root of the segtree

// Segtree seg = Segtree(MAX);
// seg.create();
// seg.create();

const int MAX = 1e9+10;
const long long INF = 1e18+10; 

typedef long long ftype;
 
struct Segtree {
    vector<ftype> seg, d, e, lazy;
    const ftype NEUTRAL = 0;
    const ftype NEUTRAL_LAZY = -INF;
    int n;
    
    Segtree(int n) {
        this->n = n;
    }
    
    ftype apply_lazy(ftype a, ftype b, int len) {
        if (b == NEUTRAL_LAZY) return a;
        else return b * len;
    }
 
    void propagate(int pos, int ini, int fim) {
        if (seg[pos] == 0) return;
        
        if (ini == fim) {
            return;
        }
 
        int m = (ini + fim) >> 1;
        
        if (e[pos] == 0) e[pos] = create();
        if (d[pos] == 0) d[pos] = create();
 
        lazy[e[pos]] = apply_lazy(lazy[e[pos]], lazy[pos], 1);
        lazy[d[pos]] = apply_lazy(lazy[d[pos]], lazy[pos], 1);
 
        seg[e[pos]] = apply_lazy(seg[e[pos]], lazy[pos], m - ini + 1);
        seg[d[pos]] = apply_lazy(seg[d[pos]], lazy[pos], fim - m);
 
        lazy[pos] = NEUTRAL_LAZY;
    }
    
    ftype f(ftype a, ftype b) {
        return a + b;
    }
 
    ftype create() {
        seg.push_back(0);
        e.push_back(0);
        d.push_back(0);
        lazy.push_back(-1);
        return seg.size() - 1;
    }
    
    ftype query(int pos, int ini, int fim, int p, int q) {
        propagate(pos, ini, fim);
        if (q < ini || p > fim) return NEUTRAL;
        if (pos == 0) return 0;
        if (p <= ini && fim <= q) return seg[pos];
        int m = (ini + fim) >> 1;
        return f(query(e[pos], ini, m, p, q), query(d[pos], m + 1, fim, p, q));
    }
 
    void update(int pos, int ini, int fim, int p, int q, int val) {
        propagate(pos, ini, fim);
        if (ini > q || fim < p) {
            return;
        }
 
        if (ini >= p && fim <= q) {
            lazy[pos] = apply_lazy(lazy[pos], val, 1);
            seg[pos] = apply_lazy(seg[pos], val, fim - ini + 1);
 
            return;
        }
 
        int m = (ini + fim) >> 1;
 
        if (e[pos] == 0) e[pos] = create();
        update(e[pos], ini, m, p, q, val);
 
        if (d[pos] == 0) d[pos] = create();
        update(d[pos], m + 1, fim, p, q, val);
 
        seg[pos] = f(seg[e[pos]], seg[d[pos]]);
    }
 
    ftype query(int p, int q) {
        return query(1, 1, n, p, q);
    }
 
    void update(int p, int q, int val) {
        update(1, 1, n, p, q, val);
    }
};
