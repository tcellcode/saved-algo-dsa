#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define oo (int)(1e18)
#define N (int)(1e5 + 5)
 
int n, m, id[N], low[N], dfstime, art, bridge;
vector<pair<int, int>> adj[N];

void find_art_bridge(int u, int p_edge = 0)
{
    low[u] = id[u] = ++dfstime;
    int child = (p_edge != 0);

    for (auto [v, i] : adj[u])
    {

        if (i == p_edge) continue;

        if (id[v]) low[u] = min(low[u], id[v]);
        else
        {
            
            find_art_bridge(v, i);
            low[u] = min(low[u], low[v]);
            if (low[v] >= id[u]) ++child;
            if (low[v] > id[u]) ++bridge;
        }
    }
    if (child > 1) ++art;
}

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v; cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    for (int i = 1; i <= n; i++)
    {
        if (!id[i])
        {
            find_art_bridge(i);
        }
    }
    cout << art << " " << bridge;
}

signed main() {
    fastio;
    solve();
    return 0;
}
