class BinaryLifting {
    public:
      vector<int> height, parent;
      vector<vector<int>> kthParent;
      int m;
      
    BinaryLifting(int n, vector<vector<int>> adj) {
        this->m = log2(n);
        height.resize(n+1,0), parent.resize(n+1,-1);
        kthParent.resize(n+1, vector<int>(m+1,-1));

        auto dfs = [&](int node, int par, int h, auto &&self)->void{
           height[node] = h;
           parent[node] = par;
           for(auto ch: adj[node]) {
              if(ch != par) {
                 self(ch, node, h+1, self);
              }
           }
        };
        dfs(1,-1,0,dfs);

        for(int i=1; i<=n; i++) kthParent[i][0] = parent[i];
        for(int j=1; j<=m; j++) {
            for(int i=1; i<=n; i++) {
                int par = kthParent[i][j-1];
                if(par != -1) kthParent[i][j] = kthParent[par][j-1];
            }
        }
    }

    int findKthParent(int node, int k) {
        int at = node;
        for(int i=0; i<=m; i++) {
            if((1<<i) & k) {
                at = kthParent[at][i];
            }
            if(at==-1) return at;
        }
        return at;
    }
    int lca(int u, int v) {
        if(height[u] > height[v]) swap(u,v);
        int diff = height[v] - height[u];
        v = findKthParent(v, diff); //uplift the v
        if(u==v) return u;

        for(int i=m; i>=0; i--) {
            int new_u = kthParent[u][i];
            int new_v = kthParent[v][i];
            if(new_u == new_v) continue;

            u = new_u;
            v = new_v;
        }
        return parent[u];
    }
};
