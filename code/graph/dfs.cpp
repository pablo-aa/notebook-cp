// DFS
//
// Percorre todos os vertices
// priorizando profundidade
//
// O(n+m)

vector<vector<int>> g;
vector<bool> vis;

void dfs(int s){
    if(vis[s]) return;
    vis[s] = true;
    for(auto v : g[s]){
        dfs(v);
    }
}