// Description:
// Indexed at zero
// Given a N x M grid, where i represents the row and j the column, perform the following operations
// update(j, i) - update the value of grid[i][j]
// query(j1, j2, i1, i2) - return the sum of values inside the rectangle
// defined by grid[i1][j1] and grid[i2][j2] inclusive

// Problem:
// https://cses.fi/problemset/task/1739/

// Complexity:
// Time complexity:
// O(log N * log M) for both query and update
// O(N * M) for build
// Memory complexity:
// 4 * M * N

// How to use:
// Segtree2D seg = Segtree2D(n, n);
// vector<vector<int>> v(n, vector<int>(n));
// seg.build(v);

// Notes
// Indexed at zero

struct Segtree2D {
    const int MAXN = 1025;
    int N, M;
    
    vector<vector<int>> seg;

    Segtree2D(int N, int M) {
        this->N = N;
        this->M = M;
        seg.resize(2*MAXN, vector<int>(2*MAXN));
    }
    
    void buildY(int noX, int lX, int rX, int noY, int lY, int rY, vector<vector<int>> &v){
        if(lY == rY){
            if(lX == rX){
                seg[noX][noY] = v[rX][rY];
            }else{
                seg[noX][noY] = seg[2*noX+1][noY] + seg[2*noX+2][noY];
            }
        }else{
            int m = (lY+rY)/2;
    
            buildY(noX, lX, rX, 2*noY+1, lY, m, v);
            buildY(noX, lX, rX, 2*noY+2, m+1, rY, v);
    
            seg[noX][noY] = seg[noX][2*noY+1] + seg[noX][2*noY+2];
        }
    }
    
    void buildX(int noX, int lX, int rX, vector<vector<int>> &v){
        if(lX != rX){
            int m = (lX+rX)/2;
    
            buildX(2*noX+1, lX, m, v);
            buildX(2*noX+2, m+1, rX, v);
        }
    
        buildY(noX, lX, rX, 0, 0, M - 1, v);
    }
    
    void updateY(int noX, int lX, int rX, int noY, int lY, int rY, int y){
        if(lY == rY){
            if(lX == rX){
                seg[noX][noY] = !seg[noX][noY];
            }else{
                seg[noX][noY] = seg[2*noX+1][noY] + seg[2*noX+2][noY];
            }
        }else{
            int m = (lY+rY)/2;
    
            if(y <= m){
                updateY(noX, lX, rX, 2*noY+1,lY, m, y);
            }else if(m < y){
                updateY(noX, lX, rX, 2*noY+2, m+1, rY, y);
            }
    
            seg[noX][noY] = seg[noX][2*noY+1] + seg[noX][2*noY+2];
        }
    }
    
    void updateX(int noX, int lX, int rX, int x, int y){
        int m = (lX+rX)/2;
    
        if(lX != rX){
            if(x <= m){
                updateX(2*noX+1, lX, m, x, y);
            }else if(m < x){
                updateX(2*noX+2, m+1, rX, x, y);
            }
        }
    
        updateY(noX, lX, rX, 0, 0, M - 1, y);
    } 
    
    int queryY(int noX, int noY, int lY, int rY, int aY, int bY){
        if(aY <= lY && rY <= bY) return seg[noX][noY];
    
        int m = (lY+rY)/2;
    
        if(bY <= m) return queryY(noX, 2*noY+1, lY, m, aY, bY);
        if(m < aY) return queryY(noX, 2*noY+2, m+1, rY, aY, bY);
    
        return queryY(noX, 2*noY+1, lY, m, aY, bY) + queryY(noX, 2*noY+2, m+1, rY, aY, bY);
    }
    
    int queryX(int noX, int lX, int rX, int aX, int bX, int aY, int bY){
        if(aX <= lX && rX <= bX) return queryY(noX, 0, 0, M - 1, aY, bY);
    
        int m = (lX+rX)/2;
    
        if(bX <= m) return queryX(2*noX+1, lX, m, aX, bX, aY, bY);
        if(m < aX) return queryX(2*noX+2, m+1, rX, aX, bX, aY, bY);
    
        return queryX(2*noX+1, lX, m, aX, bX, aY, bY) + queryX(2*noX+2, m+1, rX, aX, bX, aY, bY);
    }
    
    void build(vector<vector<int>> &v) {
        buildX(0, 0, N - 1, v);
    }
    
    int query(int aX, int bX, int aY, int bY) {
        return queryX(0, 0, N - 1, aX, bX, aY, bY);
    }
    
    void update(int x, int y) {
        updateX(0, 0, N - 1, x, y);
    }
};