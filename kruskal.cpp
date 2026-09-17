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


class MST
{
    private:
        vector<vector<pair<int, int>>> adj;
        int n;
        vector< tuple<int, int, int> > edge;
    public:
        int sum = 0;
        int edge_used = 0;
        MST(int numV)
        {
            n = numV;
            adj.resize(n + 5);
        }
        void addEdge(int u, int v, int w)
        {
            edge.push_back({u, v, w});
        }
        void buildMST()
        {
            sort(edge.begin(), edge.end(), [](const auto& t1, const auto& t2) 
            {
                return get<2>(t1) < get<2>(t2);
            });
            DSU dsu(n);
            for (auto e : edge)
            {
                if (dsu.join(get<0>(e), get<1>(e)))
                {
                    sum += get<2>(e);
                    edge_used++;
                }
            }
        }

};
