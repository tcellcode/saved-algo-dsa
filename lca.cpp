#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph
{
    private:
        // n and LOG2N MUST be declared at the top so they are initialized 
        // before being used to size the vectors below.
        int n;
        int LOG2N = 30;
        
        vector<vector<pair<int, int>>> adj;
        // Swapped dimensions: [j][i] means 2^j th ancestor of i
        vector<vector<int>> par; 
        vector<vector<int>> maxEdge;
        vector<int> depth;
 
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
        // Member initializer list directly constructs vectors with target sizes.
        // It is perfectly safe to use 'n(n)' where the parameter shares the member's name.
        Graph(int n) 
            : n(n), 
              adj(n + 5), 
              par(LOG2N + 5, vector<int>(n + 5, 0)), 
              maxEdge(LOG2N + 5, vector<int>(n + 5, 0)), 
              depth(n + 5, 0)
        {
            // Empty body: zero reallocation overhead
        }
        
        void addEdge(int u, int v, int w)
        {
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        void buildlca()
        {
            for (int i = 1; i <= n; i++) 
            {
                if (depth[i] == 0) 
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
            
            // Bring u to the same depth as v
            for (int i = LOG2N; i >= 0; i--) 
            {
                if (depth[u] - depth[v] >= (1 << i)) 
                {
                    res = max(res, maxEdge[i][u]); 
                    u = par[i][u];
                }
            }
            
            if (u == v) return res;
            
            // Both u and v jump upwards
            for (int i = LOG2N; i >= 0; i--) 
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
