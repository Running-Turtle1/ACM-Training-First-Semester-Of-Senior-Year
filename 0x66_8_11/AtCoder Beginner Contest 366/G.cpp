#include <bits/stdc++.h>
using namespace std;
#define int long long
using ll = long long;

int const N = 61;

struct Matrix {
    int n, m;
    vector<bitset<N>> data;

    Matrix(int h, int w) : n(h), m(w), data(h) {}

    bitset<N> &operator[](int i) { return data[i]; }
    // 0-无解 1-唯一解 2-无穷解
    int gauss(vector<int> &ans) {
        vector<int> where(m - 1, -1);
        for (int row = 0, col = 0; row < n && col < m - 1; ++ col) {
            for (int i = row; i < n; ++ i) {
                if (data[i][col]) {
                    swap(data[row], data[i]);
                    break;
                }
            }
            if (!data[row][col]) continue;

            where[col] = row;
            for (int i = 0; i < n; ++ i) {
                if (i != row && data[i][col]) data[i] ^= data[row];
            }
            ++ row;
        }
        ans.assign(m - 1, 0);
        for (int i = 0; i < m - 1; ++ i) {
            if (where[i] != -1) ans[i] = data[where[i]][m - 1];
        }
        for (int i = 0; i < n; ++ i) {
            int sum = 0;
            for (int j = 0; j < m - 1; ++ j) sum ^= data[i][j] * ans[j];
            if (sum != data[i][m - 1]) return 0;
        }

        for (int i = 0; i < m - 1; ++ i) {
            if (where[i] == -1) return 2;
        }
        return 1;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    Matrix g(n + 1, n + 1);
    while (m --) {
        int u, v;
        cin >> u >> v;
        -- u, -- v;
        g[u][v] = g[v][u] = 1;
    }

    vector<ll> ans(n);
    for (int i = 0; i < n; ++ i) { // 第 i 位
        Matrix m = g;
        m[n][i] = 1, m[n][n] = 1;
        vector<int> res;
        if (!m.gauss(res)) return cout << "No\n", 0;
        for (int j = 0; j < n; ++ j) {
            if (res[j]) ans[j] |= 1ll << i;
        }
    }
    cout << "Yes\n";
    for (auto x : ans) cout << x << ' ';

}

// 曼哈顿与切比雪夫
// 高斯消元
// 线性基
// bitset 优化