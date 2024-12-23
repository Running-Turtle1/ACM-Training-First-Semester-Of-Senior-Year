#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int N = 3100, M = 1E5 + 10;

int n, m, k;
int d[N][N], st[N][N];
char g[N][N];
pair<int, int> body[M];

struct node{
    int dis, x, y;
    bool operator < (const node & T) const {
        return dis > T.dis;
    }
};

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void dijkstra(){
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            d[i][j] = 1e18;       
        }
    }
    priority_queue<node> heap;
    auto &[x, y] = body[k];
    d[x][y] = 0;
    heap.push({0, x, y});
    while(heap.size()){
        auto [dis, x, y] = heap.top();
        heap.pop();

        if(st[x][y]) continue ;
        st[x][y] = 1;

        for(int dr = 0; dr < 4; dr ++){
            int nx = x + dx[dr], ny = y + dy[dr];
            if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && !st[nx][ny] && g[x][y] != '#' && d[x][y] + 1 < d[nx][ny]){
                d[nx][ny] = d[x][y] + 1;
                heap.push({d[nx][ny], nx, ny});
            }
        }
    }
}

void solve(){
    cin >> n >> m >> k;

    for(int i = 1; i <= k; i ++){
        int x, y;
        cin >> x >> y;
        body[i] = {x, y};
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            cin >> g[i][j];       
        }
    }
    dijkstra();
    for(int i = 1; i <= k; i ++){
        auto &[x, y] = body[i];
        d[x][y] = max(d[x][y], k - i + 1);
    }
    __int128 res = 0;
    const int MOD = (1LL << 64);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            if(d[i][j] != 1e18){
                (res = res + d[i][j] * d[i][j]) % MOD;
            }       
        }
    }
    cout << (int)res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}