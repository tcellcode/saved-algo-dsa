// point update

void update(int id, int l, int r, int i, int val)
{
     if (i < l || r < i) return;
     if (l == r)
     {
          st[id] = val;
          return;
     }
     int mid = (l + r) / 2;
     update(2 * id, l, mid, i, val);
     update(2 * id + 1, mid + 1, r, i, val);
     st[id] = min(st[2 * id], st[2 * id + 1]);
}

int get(int id, int l, int r, int u, int v)
{
     if (v < l || r < u) return oo;
     if (u <= l && r <= v)
     {
          return st[id];
     }
     int mid = (l + r) / 2;
     return min(get(2 * id, l, mid, u, v), get(2 * id + 1, mid + 1, r, u, v));
}








//////////
