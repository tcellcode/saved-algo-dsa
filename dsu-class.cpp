#include <vector>

class DSU {
private:
    std::vector<int> parent;

public:
    // Initialize the DSU with 'n' elements
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Each element is initially its own root
        }
    }

    // Find operation with Path Compression
    int find(int u) {
        if (parent[u] == u) {
            return u;
        }
        // Compress the path by pointing directly to the root
        return parent[u] = find(parent[u]);
    }

    // Union operation
    // Returns true if a merge happened, false if they were already connected
    bool join(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        // If they have the same root, they are already in the same set
        if (rootU == rootV) {
            return false;
        }

        // Merge the sets
        parent[rootU] = rootV;
        return true; 
    }
};
