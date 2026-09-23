#include <vector>
#include <iostream>

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
            
            // Apply to left child
            apply_op(st[id << 1], lazy[id], mid - l + 1);
            compose_op(lazy[id << 1], lazy[id]);
            
            // Apply to right child
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
    LazySegmentTree(const std::vector<ValueType>& arr, 
                    ValueType identity_Value, LazyType identity_Lazy,
                    CombineFunc combine_func, ApplyFunc apply_func, ComposeFunc compose_func) 
        : id_Value(identity_Value), id_Lazy(identity_Lazy), 
          combine(combine_func), apply_op(apply_func), compose_op(compose_func) {
        
        n = arr.size() - 1;
        st.assign(4 * n + 1, id_Value);
        lazy.assign(4 * n + 1, id_Lazy);
        if (n > 0) {
            build(1, 1, n, arr);
        }
    }

    void update(int u, int v, LazyType val) {
        update(1, 1, n, u, v, val);
    }

    ValueType query(int u, int v) {
        return query(1, 1, n, u, v);
    }
};
