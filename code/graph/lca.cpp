// LCA
//
// lowest common ancestor between two nodes
//
// edit_distance(n, adj, root)
// 
// https://cses.fi/problemset/task/1688
//
// O(log N)

struct LCA {
  const int MAXE = 31;
  vector<vector<int>> up;
  vector<int> dep;
  
  LCA(int n, vector<vector<int>>& adj, int root = 1) {
    up.assign(n+1, vector<int>(MAXE, -1));
    dep.assign(n+1, 0);
    
    dep[root] = 1;
    dfs(root, -1, adj);
 
    for (int j = 1; j < MAXE; j++) {
      for (int i = 1; i <= n; i++) {
        if (up[i][j-1] != -1)
          up[i][j] = up[ up[i][j-1] ][j-1];
      }
    }
  }
 
  void dfs(int x, int p, vector<vector<int>>& adj) {
    up[x][0] = p;
    for (auto e : adj[x]) {
      if (e != p) {
        dep[e] = dep[x] + 1;
        dfs(e, x, adj);
      }
    }
  }
 
  int jump(int x, int k) { // jump from node x k times
    for (int i = 0; i < MAXE; i++) {
      if (k&(1 << i) && x != -1) x = up[x][i];
    }
    return x;
  }
 
  int lca(int a, int b) {
    if (dep[a] > dep[b]) swap(a, b);
    b = jump(b, dep[b] - dep[a]);
 
    if (a == b) return a;
    
    for (int i = MAXE-1; i >= 0; i--) {
      if (up[a][i] != up[b][i]) {
        a = up[a][i];
        b = up[b][i];
      }
    }
 
    return up[a][0];
  }
 
  int dist(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
  }
};