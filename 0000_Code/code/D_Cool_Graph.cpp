#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int N = 1E5 + 10;

int n, m;
int d[N], p[N];

set<int> edges[N];

int find(int x) {
    return x == p[x] ? x : p[x] = find(p[x]);
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        d[i] = 0;
        p[i] = i;
        edges[i].clear();
    }

    auto add = [&] (int x, int y) {
        edges[x].insert(y);
        edges[y].insert(x);
        ++ d[x], ++ d[y];
    };
    auto del = [&] (int x, int y) {
        edges[x].erase(y);
        edges[y].erase(x);
        -- d[x], -- d[y];
    };

    for(int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        add(x, y);
    }
    
    vector<tuple<int, int, int> > res;

    for(int i = 1; i <= n; i ++) {
        while(d[i] >= 2) {
            auto it1 = edges[i].begin();
            auto it2 = next(it1);
            int v1 = *it1, v2 = *it2;
            res.push_back({i, v1, v2});
            del(i, v1), del(i, v2);
            if(edges[v1].count(v2)) del(v1, v2);
            else add(v1, v2);
        }
    }

    int x = -1, y = -1;
    for(int i = 1; i <= n; i ++) {
        if(edges[i].size()) {
            for(auto j : edges[i]) {
                int pi = find(i), pj = find(j);
                if(pi != pj) p[pj] = pi;
                x = i, y = j;
            }
        }
    }

    if(x != -1) {
        for(int i = 1; i <= n; i ++) {
            int pi = find(i), pnow = find(x);
            if(pnow != pi) {
                res.push_back({x, y, pi});
                p[pnow] = pi;
                x = pi;
            }
        }
    }

    cout << res.size() << '\n';
    for(auto &[a, b, c] : res) cout << a << ' ' << b << ' ' << c << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}