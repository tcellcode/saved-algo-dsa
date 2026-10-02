void tarjan(int u, int p = -1)
{
     low[u] = id[u] = ++dfstime;
     s.push(u);
     
     for (auto v : g[u])
     {    
          if (id[v]) low[u] = min(low[u], id[v]);
          else
          {
               tarjan(v);
               low[u] = min(low[u], low[v]);

              if (low[to] > tin[v])
                IS_BRIDGE(v, to);
          
          }
     }
     
     if (low[u] == id[u])
     {
          ++scc; 
          int v;
          do
          {
               v = s.top();
               s.pop();  
               vis[v] = 1;
          } while (v != u);
     }
}
