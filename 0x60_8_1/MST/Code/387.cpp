#include <bits/stdc++.h>
using namespace std;
#define int long long

int s, p;
pair<int, int> at[510];

double const eps = 1e-6;

int fa[510];
int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        fa[rootY] = rootX;
    }
}

double dis[510][510];

double computeDistance(int x, int y) {
    auto &[x1, y1] = at[x];
    auto &[x2, y2] = at[y];
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool check(double d) {
    for (int i = 1; i <= p; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= p; j++) {
            if (dis[i][j] <= d) {
                unionSets(i, j);
            }
        }
    }
    int components = 0;
    for (int i = 1; i <= p; i++) {
        if (find(i) == i) components++;
    }
    return components <= s;
}

void solve() {
    cin >> s >> p;
    for (int i = 1; i <= p; i++) {
        cin >> at[i].first >> at[i].second;
    }
    for (int i = 1; i <= p; i++) {
        for (int j = 1; j < i; j++) {
            dis[i][j] = dis[j][i] = computeDistance(i, j);
        }
        dis[i][i] = 0;
    }
    double l = 0, r = 30000;
    while (r - l > eps) {
        double mid = (l + r) / 2.0;
        if (check(mid)) r = mid;
        else l = mid;
    }
    cout << fixed << setprecision(2) << l << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    int T;
    cin >> T;
    while (T--) {
        solve();    
    }
    
    return 0;
}