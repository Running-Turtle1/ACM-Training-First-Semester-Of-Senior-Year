#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int N = 350 + 1;
constexpr int inf = 1E9 + 1;

void chmax(int &x, int y){
	if(x < y){
		x = y;
	}
}
 
int main () {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    int n, k;
    cin >> n >> k;
 
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
 
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x --, y --;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
 
    vector<int> siz(n, 1);
    vector<vector<array<array<int, 2>, 2>>> f(n);
    vector<vector<vector<array<int, 2>>>> g(n);
 
    auto dfs = [&](auto self, int x, int p = -1) -> void {
        int C = 0;
        g[x].assign(2, vector (1, array {-inf, -inf}));
        g[x][0][0][a[x]] = g[x][1][0][!a[x]] = 0;
        for (int y : adj[x]) {
            if (y == p) {
                continue;
            }
            self(self, y, x);
            C++;
             
            vector ng(siz[x] + siz[y] + 1, vector<array<int, 2>> (C + 1, {-inf, -inf}));
            for (int t = 0; t < 2; t++) {
                for (int i = 0; i <= siz[x]; i++) {
                    for (int j = 0; j <= siz[y]; j++) {
                        for (int k = 0; k < C; k++) {
                            chmax(ng[i + j][k + 1][t], g[x][i][k][t] + f[y][j][!t][t]);
                            chmax(ng[i + j][k][t], g[x][i][k][t] + f[y][j][t][t]);
                        }
                    }
                }
            }
            g[x] = move(ng);
 
            siz[x] += siz[y];
        }
 
        f[x].assign(siz[x] + 1, array<array<int, 2>, 2> {-inf, -inf, -inf, -inf});
        for (int i = 0; i <= siz[x]; i++) {
            for (int j = 0; j <= C; j++) {
                for (int t = 0; t < 2; t++) {
                    for (int tp = 0; tp < 2; tp++) {
                        int nj = j + (t != tp);
                        chmax(f[x][i][t][tp], g[x][i][j][t] + nj * (nj - 1) * (nj - 2) / 6);
                    }
                }
            }
        }
    };
 
    dfs(dfs, 0);
 
    int ans = -inf;
    for (int i = 0; i <= k; i++) {
        for (int t = 0; t < 2; t++) {
            chmax(ans, f[0][i][t][t]);
        }
    }
 
    cout << ans << "\n";
 
    return 0;
}