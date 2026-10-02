// g[u] represents an undirected adjacency list
// id[u] stores the discovery time of node u
// low[u] stores the lowest discovery time reachable from u
int dfstime = 0;
vector<int> id, low; 

void find_art_bridge(int u, int p = -1) 
{
    low[u] = id[u] = ++dfstime;

    for (auto v : g[u]) 
    {
        if (v == p) continue; // Skip the edge leading back to the parent

        if (id[v]) 
        {
            // Back-edge found: update low link with neighbor's discovery time
            low[u] = min(low[u], id[v]);
        } 
        else 
        {
            // Forward-edge: visit the unvisited neighbor
            find_art_bridge(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= id[u]) ++child;
            // Bridge condition: if v cannot reach u or any ancestor of u
            if (low[v] > id[u]) 
            {
                IS_BRIDGE(u, v); 
            }
        }
    }

    if (child > 1) IS_CUTPOINT(u);
}
