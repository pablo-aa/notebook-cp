// Description:
// Persistent segtree allows for you to save the different versions of the segtree between each update
// Indexed at one
// Query - get sum of elements from range (l, r) inclusive
// Update - update element at position id to a value val

// Problem:
// https://cses.fi/problemset/task/1737/

// Complexity:
// O(log n) for both query and update

// How to use:
// vector<int> raiz(MAX); // vector to store the roots of each version
// Segtree seg = Segtree(INF);
// raiz[0] = seg.create(); // null node
// curr = 1; // keep track of the last version

// raiz[k] = seg.update(raiz[k], idx, val); // updating version k
// seg.query(raiz[k], l, r) // querying version k
// raiz[++curr] = raiz[k]; // create a new version based on version k

const int MAX = 2e5+17;
const int INF = 1e9+17;

typedef long long ftype;

struct Segtree {
    vector<ftype> seg, d, e;
    const ftype NEUTRAL = 0;
    int n;
    
    Segtree(int n) {
        this->n = n;
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
 
    int update(int pos, int ini, int fim, int id, int val) {
        int novo = create();
        
        seg[novo] = seg[pos];
        e[novo] = e[pos];
        d[novo] = d[pos];
        
        if (ini == fim) {
            seg[novo] = val;
            return novo;
        }
        
        int m = (ini + fim) >> 1;
        
        if (id <= m) e[novo] = update(e[novo], ini, m, id, val);
        else d[novo] = update(d[novo], m + 1, fim, id, val);
        
        seg[novo] = f(seg[e[novo]], seg[d[novo]]);
        
        return novo;
    }
 
    ftype query(int pos, int p, int q) {
        return query(pos, 1, n, p, q);
    }
 
    int update(int pos, int id, int val) {
        return update(pos, 1, n, id, val);
    }
};