// Ford-Fulkerson
//
// max-flow / min-cut
//
// MAX nós
// 
// https://cses.fi/problemset/task/1694/
//
// O(m * max_flow)

using ll = long long;
const int MAX = 510;

struct Flow {
    int n;
    ll adj[MAX][MAX];
    bool used[MAX];
    
    Flow(int n) : n(n) {};
    
    void add_edge(int u, int v, ll c) {
        adj[u][v] += c;
        adj[v][u] = 0; // cuidado com isso
    }
    
    ll dfs(int x, int t, ll amount) {
        used[x] = true;
        
        if (x == t) return amount;
        
        for (int i = 1; i <= n; i++) {
            if (adj[x][i] > 0 && !used[i]) {
                ll sent = dfs(i, t, min(amount, adj[x][i]));
                
                if (sent > 0) {
                    adj[x][i] -= sent;
                    adj[i][x] += sent;
                    
                    return sent;
                }
            }
        }
        
        return 0;
    }
    
    ll max_flow(int s, int t) { // source and sink
        ll total = 0;
        ll sent = -1;
        
        while (sent != 0) {
            memset(used, 0, sizeof(used));
            sent = dfs(s, t, INT_MAX);
            total += sent;
        }
        
        return total;
    }
};