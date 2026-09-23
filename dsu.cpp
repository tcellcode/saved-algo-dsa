#include <vector>
#include <numeric> // Optional: for std::iota
using namespace std;

class DSU
{
    private: 
        vector<int> par;
        vector<int> sz;
    public:
        // Use the member initializer list to construct vectors with their target size directly
        DSU(int n) : par(n + 5), sz(n + 5, 1)
        {
            // The vectors are already sized correctly before this block runs.
            // We just need to set the parent indices.
            for (int i = 1; i <= n; i++) par[i] = i;
            
            // Bonus C++ trick: You can replace the for loop above with std::iota
            // std::iota(par.begin(), par.end(), 0); // Fills vector with 0, 1, 2, 3...
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
