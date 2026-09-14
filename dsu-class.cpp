#include <vector>
#include <algorithm> // For std::swap

class DSU {
private:
    std::vector<int> parent;
    std::vector<int> size; // Added to track the size of each set

public:
    // Initialize the DSU with 'n' elements
    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1); // Every set initially has a size of 1
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

    // Union operation with Union by Size
    // Returns true if a merge happened, false if they were already connected
    bool join(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        // If they have the same root, they are already in the same set
        if (rootU == rootV) {
            return false;
        }

        // Ensure rootU represents the larger set
        if (size[rootU] < size[rootV]) {
            std::swap(rootU, rootV);
        }

        // Merge the smaller set (rootV) into the larger set (rootU)
        parent[rootV] = rootU;
        
        // Update the size of the new combined set
        size[rootU] += size[rootV];
        
        return true; 
    }
};
