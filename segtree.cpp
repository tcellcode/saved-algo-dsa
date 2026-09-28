#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define oo (int)(1e18) 
 
template <typename ValueType, typename LazyType,         
          typename CombineFunc, typename ApplyFunc, typename ComposeFunc>
class LazySegmentTree {
private:
    int n;
    std::vector<ValueType> st;
    std::vector<LazyType> lazy;
    
    ValueType id_Value; 
    LazyType id_Lazy;    
 
    CombineFunc combine;
    ApplyFunc apply_op;
    ComposeFunc compose_op;
 
    void build(int id, int l, int r, const std::vector<ValueType>& arr) {
        if (l == r) {
            st[id] = arr[l]; 
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid, arr);
        build((id << 1) | 1, mid + 1, r, arr);
        st[id] = combine(st[id << 1], st[(id << 1) | 1]);
    }
 
    void push(int id, int l, int r) {
        if (lazy[id] != id_Lazy) {
            int mid = (l + r) >> 1;
            
            apply_op(st[id << 1], lazy[id], mid - l + 1);
            compose_op(lazy[id << 1], lazy[id]);
            
            apply_op(st[(id << 1) | 1], lazy[id], r - mid);
            compose_op(lazy[(id << 1) | 1], lazy[id]);
            
            lazy[id] = id_Lazy;
        }
    }
 
    void update(int id, int l, int r, int u, int v, LazyType val) {
        if (r < u || v < l) return;
        if (u <= l && r <= v) {
            apply_op(st[id], val, r - l + 1);
            compose_op(lazy[id], val);
            return;
        }
        push(id, l, r);
        int mid = (l + r) >> 1;
        update(id << 1, l, mid, u, v, val);
        update((id << 1) | 1, mid + 1, r, u, v, val);
        st[id] = combine(st[id << 1], st[(id << 1) | 1]);
    }
 
    ValueType query(int id, int l, int r, int u, int v) {
        if (r < u || v < l) return id_Value;
        if (u <= l && r <= v) return st[id];
        push(id, l, r);
        int mid = (l + r) >> 1;
        return combine(
            query(id << 1, l, mid, u, v),
            query((id << 1) | 1, mid + 1, r, u, v)
        );
    }
 
public:
    LazySegmentTree(ValueType identity_Value, LazyType identity_Lazy,
                    CombineFunc combine_func, ApplyFunc apply_func, ComposeFunc compose_func) 
        : n(0), id_Value(identity_Value), id_Lazy(identity_Lazy), 
          combine(combine_func), apply_op(apply_func), compose_op(compose_func) {
        st.resize(4 * 200005 + 1, id_Value);
        lazy.resize(4 * 200005 + 1, id_Lazy);
    }
 
    void init_once(int new_n) {
        n = new_n;
    }
 
    void update(int u, int v, LazyType val) {
        update(1, 1, n, u, v, val);
    }
 
    ValueType query(int u, int v) {
        return query(1, 1, n, u, v);
    }
};
 
struct Node {
    int mn, mx;
    bool operator!=(const Node& other) const {
        return mn != other.mn || mx != other.mx;
    }
};
 
struct CombineNode {
    Node operator()(const Node& a, const Node& b) const {
        return {min(a.mn, b.mn), max(a.mx, b.mx)};
    }
};
struct ApplyNode {
    void operator()(Node& val, const Node& lazy, int len) const {
        val = lazy; 
    }
};
struct ComposeNode {
    void operator()(Node& curr, const Node& lazy) const {
        curr = lazy;
    }
};
 
const Node id_val = {oo, -oo};
const Node id_lazy = {oo, -oo};
static LazySegmentTree<Node, Node, CombineNode, ApplyNode, ComposeNode> segtree(id_val, id_lazy, CombineNode{}, ApplyNode{}, ComposeNode{});
