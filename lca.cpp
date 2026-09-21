class Graph
{
    private:
        vector<vector<pair<int, int>>> adj;
        // Swapped dimensions: [j][i] means 2^j th ancestor of i
        vector<vector<int>> par; 
        vector<vector<int>> maxEdge;
        vector<int> depth;
        int n, LOG2N = 30;
 
        void dfs(int u, int p)
        {
            for (auto v : adj[u])
            {
                if (v.first == p) continue;
                depth[v.first] = depth[u] + 1;
                par[0][v.first] = u;
                maxEdge[0][v.first] = v.second;
                dfs(v.first, u);
            }
        }
 
    public:
        Graph(int numU)
        {
            n = numU;
            adj.resize(n + 5);
            depth.resize(n + 5, 0); 
            // Resize outer vector to LOG2N + 5, inner vector to n + 5
            par.assign(LOG2N + 5, vector<int>(n + 5, 0));
            maxEdge.assign(LOG2N + 5, vector<int>(n + 5, 0));
        }
        
        void addEdge(int u, int v, int w)
        {
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        void buildlca()
        {
            for(int i = 1; i <= n; i++) 
            {
                if(depth[i] == 0) 
                {
                    depth[i] = 1;
                    par[0][i] = i;
                    dfs(i, i);
                }
            }
            for (int j = 1; j <= LOG2N; j++)
            {
                for (int i = 1; i <= n; i++)
                {
                    par[j][i] = par[j - 1][ par[j - 1][i] ]; 
                    maxEdge[j][i] = max(maxEdge[j - 1][i], maxEdge[j - 1][ par[j - 1][i] ]);
                }
            }
        }
        
        int lca(int u, int v)
        {
            int res = 0;
            if (depth[u] < depth[v]) swap(u, v); 
            
            for (int i = LOG2N; i >= 0; i--) // bring u to the same depth as v
            {
                if (depth[u] - depth[v] >= (1 << i)) 
                {
                    res = max(res, maxEdge[i][u]); 
                    u = par[i][u];
                }
            }
            
            if (u == v) return res;
            
            for (int i = LOG2N; i >= 0; i--) // u, v both jump
            {
                if (par[i][u] != par[i][v])
                {
                    res = max({res, maxEdge[i][u], maxEdge[i][v]}); 
                    u = par[i][u];
                    v = par[i][v];
                }
            }
            
            res = max({res, maxEdge[0][u], maxEdge[0][v]});
            return res;
        }
        
        int acs(int u, int k)
        {
            if (depth[u] - 1 < k) return -1;
            for (int i = 0; i <= LOG2N; i++)
            {
                if (k & (1 << i))
                {
                    u = par[i][u];
                }
            }
            return u;
        }
};
