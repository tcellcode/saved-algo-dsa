class Graph
{
    private:
        vector<vector<pair<int, int>>> adj;
        vector<vector<int>> par;
        vector<vector<int>> maxEdge;
        vector<int> depth;
        int n, LOG2N;
 
        void dfs(int u, int p)
        {
            for (auto v : adj[u])
            {
                if (v.first == p) continue;
                depth[v.first] = depth[u] + 1;
                par[v.first][0] = u;
                maxEdge[v.first][0] = v.second;
                dfs(v.first, u);
            }
        }
 
    public:
        Graph(int numU)
        {
            n = numU;
            LOG2N = (int)log2(n);
            adj.resize(n + 5);
            depth.resize(n + 5, 0); 
            par.assign(n + 5, vector<int>(LOG2N + 5, 0));
            maxEdge.assign(n + 5, vector<int>(LOG2N + 5, 0));
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
                    par[i][0] = i;
                    dfs(i, i);
                }
            }
            for (int j = 1; j <= LOG2N; j++)
            {
                for (int i = 1; i <= n; i++)
                {
                    par[i][j] = par[ par[i][j - 1] ][j - 1];
                    maxEdge[i][j] = max(maxEdge[i][j - 1], maxEdge[ par[i][j - 1] ][j - 1]);
                }
            }
        }
        int lca(int u, int v)
        {
            int res = 0;
            if (depth[u] < depth[v]) swap(u, v); 
            for (int i = LOG2N; i >= 0; i--) // bring u to the same depth as v
            {
                if (depth[u] - depth[v] >= (1 << i)) // can u do a 2^i jump
                {
                    res = max(res, maxEdge[u][i]); // update res first
                    u = par[u][i];
                }
            }
            if (u == v) return res;
            for (int i = LOG2N; i >= 0; i--) // u, v both jump
            {
                if (par[u][i] != par[v][i])
                {
                    res = max({res, maxEdge[u][i], maxEdge[v][i]}); // update res first
                    u = par[u][i];
                    v = par[v][i];
                }
            }
            res = max({res, maxEdge[u][0], maxEdge[v][0]});
            return res;
        }
 
};
