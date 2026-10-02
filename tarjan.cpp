void tarjan(int u, int p = -1)
{
     low[u] = id[u] = ++dfstime;
     s.push(u);
     
     for (auto v : g[u])
     {
          if (onstack[v]) continue;
          
          if (id[v]) low[u] = min(low[u], id[v]);
          else
          {
               tarjan(v, u);
               low[u] = min(low[u], low[v]);
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
               onstack[v] = 1;
          } while (v != u);
     }
}
