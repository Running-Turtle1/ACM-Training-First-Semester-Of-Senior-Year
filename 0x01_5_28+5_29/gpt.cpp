#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class UnionFind {
public:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
    
    int find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
        }
        if (x != parent[x]) {
            int original_parent = parent[x];
            parent[x] = find(parent[x]);
            rank[x] = (rank[x] + rank[original_parent]) % 2;
        }
        return parent[x];
    }
    
    void unite(int x, int y, int e) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
            rank[rootX] = (rank[y] - rank[x] + e + 2) % 2;
        }
    }
};

void solve() {
    int n;
    cin >> n;
    
    UnionFind uf;
    vector<tuple<int, int, int>> constraints;
    
    for (int i = 0; i < n; ++i) {
        int x, y, e;
        cin >> x >> y >> e;
        constraints.push_back(make_tuple(x, y, e));
    }
    
    // First, process all equality constraints
    for (const auto& [x, y, e] : constraints) {
        if (e == 1) {
            uf.unite(x, y, 0);
        }
    }
    
    // Then, process all inequality constraints
    bool satisfiable = true;
    for (const auto& [x, y, e] : constraints) {
        if (e == 0) {
            if (uf.find(x) == uf.find(y)) {
                if (uf.rank[x] == uf.rank[y]) {
                    satisfiable = false;
                    break;
                }
            }
        }
    }
    
    cout << (satisfiable ? "YES" : "NO") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}