#include <iostream>
#include <vector>
#include <functional>

template <typename T, typename L>
class LazySegmentTree {
private:
    int n;
    std::vector<T> st;
    std::vector<L> lazy;
    
    T id_T; // Identity element for the node (e.g., 0 for sum)
    L id_L; // Identity element for the lazy tag (e.g., 0 for "no pending update")

    // Function to merge two child nodes
    std::function<T(T, T)> combine;
    // Function to apply a lazy tag to a node
    std::function<void(T&, L, int)> apply_op;
    // Function to merge a new lazy tag into an existing one
    std::function<void(L&, L)> compose_op;

    void build(int id, int l, int r, const std::vector<T>& arr) {
        if (l == r) {
            st[id] = arr[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(2 * id, l, mid, arr);
        build(2 * id + 1, mid + 1, r, arr);
        st[id] = combine(st[2 * id], st[2 * id + 1]);
    }

    void push(int id, int l, int r) {
        if (lazy[id] != id_L) {
            int mid = (l + r) >> 1;
            
            // Apply to left child
            apply_op(st[2 * id], lazy[id], mid - l + 1);
            compose_op(lazy[2 * id], lazy[id]);
            
            // Apply to right child
            apply_op(st[2 * id + 1], lazy[id], r - mid);
            compose_op(lazy[2 * id + 1], lazy[id]);
            
            // Clear current node's lazy tag
            lazy[id] = id_L;
        }
    }

    void update(int id, int l, int r, int u, int v, L val) {
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

    T query(int id, int l, int r, int u, int v) {
        if (r < u || v < l) return id_T;
        if (u <= l && r <= v) return st[id];
        push(id, l, r);
        int mid = (l + r) >> 1;
        return combine(
            query(2 * id, l, mid, u, v),
            query(2 * id + 1, mid + 1, r, u, v)
        );
    }

public:
    LazySegmentTree(const std::vector<T>& arr, 
                    T identity_T, L identity_L,
                    std::function<T(T, T)> combine_func,
                    std::function<void(T&, L, int)> apply_func,
                    std::function<void(L&, L)> compose_func) 
        : id_T(identity_T), id_L(identity_L), 
          combine(combine_func), apply_op(apply_func), compose_op(compose_func) {
        
        n = arr.size();
        // 1-based indexing for internal array, size 4*N is safe upper bound
        st.assign(4 * n, id_T);
        lazy.assign(4 * n, id_L);
        if (n > 0) {
            build(1, 0, n - 1, arr);
        }
    }

    // 0-indexed public wrappers
    void update(int u, int v, L val) {
        update(1, 0, n - 1, u, v, val);
    }

    T query(int u, int v) {
        return query(1, 0, n - 1, u, v);
    }
};
