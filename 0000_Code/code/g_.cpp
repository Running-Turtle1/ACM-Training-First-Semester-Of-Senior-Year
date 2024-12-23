#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int N = 3100, M = 1E5 + 10;

int n, m, k;
int d[N][N], st[N][N], hasbody[N][N];
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

inline void write(__int128 x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void dijkstra(){
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            d[i][j] = 1e18;       
        }
    }
    priority_queue<node> heap;
    auto &[x, y] = body[1];
    d[x][y] = 0;
    heap.push({0, x, y});
    while(heap.size()){
        auto [dis, x, y] = heap.top();
        heap.pop();

        if(st[x][y]) continue ;
        st[x][y] = 1;

        for(int dr = 0; dr < 4; dr ++){
            int nx = x + dx[dr], ny = y + dy[dr];
            if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && !st[nx][ny] && g[nx][ny] != '#'){
                int t = hasbody[nx][ny] ? max(d[x][y] + 1, k - hasbody[nx][ny] + 1) : (d[x][y] + 1);
                if(t < d[nx][ny]){
                    d[nx][ny] = t;
                    heap.push({t, nx, ny});
                }
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
        hasbody[x][y] = i;
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            cin >> g[i][j];       
        }
    }
    dijkstra();
    // for(int i = 1; i <= n; i ++){
    //     for(int j = 1; j <= m; j ++){
    //         cout << d[i][j] << " \n"[j == m];      
    //     }
    // }
    __int128 res = 0;
    __int128 MOD = (1LL << 62); 
    MOD = MOD * 4LL;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            if(d[i][j] != 1e18){
                res += d[i][j] * d[i][j];
                // while(res > MOD) res -= MOD;
                res = res - (res / MOD) * MOD;
                // (res = res + d[i][j] * d[i][j]) % MOD;
            }       
        }
    }
    write(res);
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