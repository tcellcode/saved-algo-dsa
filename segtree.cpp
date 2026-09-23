#include <iostream>
#include <vector>
#include <functional>

template <typename ValueType, typename LazyType>
class LazySegmentTree {
private:
    int n;
    std::vector<ValueType> st;
    std::vector<LazyType> lazy;
    
    ValueType id_Value; // Identity element for the node (e.g., 0 for sum)
    LazyType id_Lazy;   // Identity element for the lazy tag (e.g., 0 for "no pending update")

    // Function to merge two child nodes
    std::function<ValueType(ValueType, ValueType)> combine;
    // Function to apply a lazy tag to a node
    std::function<void(ValueType&, LazyType, int)> apply_op;
    // Function to merge a new lazy tag into an existing one
    std::function<void(LazyType&, LazyType)> compose_op;

    void build(int id, int l, int r, const std::vector<ValueType>& arr) {
        if (l == r) {
            // Map the 1-indexed tree range to the 0-indexed input array
            st[id] = arr[l - 1]; 
            return;
        }
        int mid = (l + r) >> 1;
        build(2 * id, l, mid, arr);
        build(2 * id + 1, mid + 1, r, arr);
        st[id] = combine(st[2 * id], st[2 * id + 1]);
    }

    void push(int id, int l, int r) {
        if (lazy[id] != id_Lazy) {
            int mid = (l + r) >> 1;
            
            // Apply to left child
            apply_op(st[2 * id], lazy[id], mid - l + 1);
            compose_op(lazy[2 * id], lazy[id]);
            
            // Apply to right child
            apply_op(st[2 * id + 1], lazy[id], r - mid);
            compose_op(lazy[2 * id + 1], lazy[id]);
            
            // Clear current node's lazy tag
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
        update(2 * id, l, mid, u, v, val);
        update(2 * id + 1, mid + 1, r, u, v, val);
        st[id] = combine(st[2 * id], st[2 * id + 1]);
    }

    ValueType query(int id, int l, int r, int u, int v) {
        if (r < u || v < l) return id_Value;
        if (u <= l && r <= v) return st[id];
        push(id, l, r);
        int mid = (l + r) >> 1;
        return combine(
            query(2 * id, l, mid, u, v),
            query(2 * id + 1, mid + 1, r, u, v)
        );
    }

public:
    LazySegmentTree(const std::vector<ValueType>& arr, 
                    ValueType identity_Value, LazyType identity_Lazy,
                    std::function<ValueType(ValueType, ValueType)> combine_func,
                    std::function<void(ValueType&, LazyType, int)> apply_func,
                    std::function<void(LazyType&, LazyType)> compose_func) 
        : id_Value(identity_Value), id_Lazy(identity_Lazy), 
          combine(combine_func), apply_op(apply_func), compose_op(compose_func) {
        
        n = arr.size();
        // 1-based indexing for internal array, size 4*N is safe upper bound
        st.assign(4 * n + 1, id_Value);
        lazy.assign(4 * n + 1, id_Lazy);
        if (n > 0) {
            build(1, 1, n, arr); // Build using 1-indexed bounds [1, n]
        }
    }

    // 1-indexed public wrappers
    void update(int u, int v, LazyType val) {
        update(1, 1, n, u, v, val);
    }

    ValueType query(int u, int v) {
        return query(1, 1, n, u, v);
    }
};
