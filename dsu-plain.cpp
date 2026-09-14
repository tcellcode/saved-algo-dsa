int par[MAXN], sz[MAXN];
for (int i = 0; i <= n; i++) {
    par[i] = i;
    sz[i] = 1;
}

// 1. Path Compression
int acs(int u) 
{
    if (par[u] == u) 
        return u;
    
    // Update the parent directly during the return step
    return par[u] = acs(par[u]); 
}

// 2. Union by Size
void join(int u, int v) 
{
    int x = acs(u);
    int y = acs(v);
    
    if (x != y) 
    {
        // Ensure x always represents the larger set
        if (sz[x] < sz[y]) 
        {
            swap(x, y); 
        }
        
        // Attach the smaller tree (y) to the larger tree (x)
        par[y] = x;     
        
        // Update the size of the new combined set
        sz[x] += sz[y]; 
    }
}
