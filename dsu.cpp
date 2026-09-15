class DSU
{
    private: 
        vector<int> par;
        vector<int> sz;
    public:
        DSU(int n)
        {
            par.resize(n + 5); sz.resize(n + 5, 1);
            for (int i = 1; i <= n; i++) par[i] = i;
            
        }

        int acs(int u)
        {
            if (par[u] == u) return u;
            return par[u] = acs(par[u]);
        }

        bool join(int u, int v)
        {
            int ru = acs(u), rv = acs(v);
            if (ru == rv) return false; // no need to join
            
            // root u has the largest size
            if (sz[ru] < sz[rv]) swap(ru, rv);
            par[rv] = ru;
            sz[ru] += sz[rv];
            return true;
        }

        bool connected(int u, int v)
        {
            int ru = acs(u), rv = acs(v);
            return (ru == rv);
        }

        
};
