void push(int id, int l, int r)
{
    int mid = l + r >> 1;
    if (lazy[id] != 0)
    {
        st[2 * id] = lazy[id] * (mid - l + 1);
        st[2 * id + 1] = lazy[id] * (r - mid);
        lazy[2 * id] = lazy[2 * id + 1] = lazy[id];
        lazy[id] = 0;
    }
}
 
void update(int id, int l, int r, int u, int v, int val)
{
    if (r < u || v < l) return;
    if (u <= l && r <= v)
    {
        st[id] = val * (r - l + 1);
        lazy[id] = val;
        return;
    }
    push(id, l, r);
    int mid = l + r >> 1;
    update(2 * id, l, mid, u, v, val);
    update(2 * id + 1, mid + 1, r, u, v, val);
    st[id] = st[2 * id] + st[2 * id + 1];
}
 
int get(int id, int l, int r, int u, int v)
{
    if (r < u || v < l) return 0;
    if (u <= l && r <= v) return st[id];
    push(id, l, r);
    int mid = l + r >> 1;
    return get(2 * id, l, mid, u, v) + get(2 * id + 1, mid + 1, r, u, v);
}
