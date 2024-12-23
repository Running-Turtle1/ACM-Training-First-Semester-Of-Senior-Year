#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, q;
struct info {
    int l, r, c;
    bool operator < (const info &T) const {
        return c < T.c;
    }
} infos[N];

int p[N];
int find(int x) {
    if(x == p[x]) return x;
    return p[x] = find(p[x]);
}

void merge(int x, int y) {
    x = find(x), y = find(y);
    if(x != y) p[x] = y;
}

void solve() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        p[i] = i;
    }
    for(int i = 1; i <= q; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        infos[i] = {l, r, c};
    }
    int res = 0;
    sort(infos + 1, infos + q + 1);
    for(int i = 1; i <= q; i++) {
        auto [l, r, c] = infos[i];
        int j = find(l);
        while(j <= r) {
            if(find(j) == find(j + 1)) {
                j = find(j + 1);
            } else {
                merge(j, j + 1);
                res += c;
                j = find(j + 1);
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        if(find(i) != find(1)) {
            res = -1;
            break;
        }
    }
    cout << res << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
