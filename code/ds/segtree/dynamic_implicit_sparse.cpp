// Description:
// Indexed at one

// When the indexes of the nodes are too big to be stored in an array
// and the queries need to be answered online so we can't sort the nodes and compress them
// we create nodes only when they are needed so there'll be (Q*log(MAX)) nodes
// where Q is the number of queries and MAX is the maximum index a node can assume

// Query - get sum of elements from range (l, r) inclusive
// Update - update element at position id to a value val

// Problem:
// https://cses.fi/problemset/task/1648

// Complexity:
// O(log n) for both query and update

// How to use:
// MAX is the maximum index a node can assume

// Segtree seg = Segtree(MAX);

typedef long long ftype;

const int MAX = 1e9+17;

struct Segtree {
    vector<ftype> seg, d, e;
    const ftype NEUTRAL = 0;
    int n;
    
    Segtree(int n) {
        this->n = n;
        create();
        create();
    }
    
    ftype f(ftype a, ftype b) {
        return a + b;
    }

    ftype create() {
        seg.push_back(0);
        e.push_back(0);
        d.push_back(0);
        return seg.size() - 1;
    }
    
    ftype query(int pos, int ini, int fim, int p, int q) {
        if (q < ini || p > fim) return NEUTRAL;
        if (pos == 0) return 0;
        if (p <= ini && fim <= q) return seg[pos];
        int m = (ini + fim) >> 1;
        return f(query(e[pos], ini, m, p, q), query(d[pos], m + 1, fim, p, q));
    }
 
    void update(int pos, int ini, int fim, int id, int val) {
        if (ini > id || fim < id) {
            return;
        }
 
        if (ini == fim) {
            seg[pos] = val;
 
            return;
        }
 
        int m = (ini + fim) >> 1;
 
        if (id <= m) {
            if (e[pos] == 0) e[pos] = create();
            update(e[pos], ini, m, id, val);
        } else {
            if (d[pos] == 0) d[pos] = create();
            update(d[pos], m + 1, fim, id, val);
        }
 
        seg[pos] = f(seg[e[pos]], seg[d[pos]]);
    }
 
    ftype query(int p, int q) {
        return query(1, 1, n, p, q);
    }
 
    void update(int id, int val) {
        update(1, 1, n, id, val);
    }
};
