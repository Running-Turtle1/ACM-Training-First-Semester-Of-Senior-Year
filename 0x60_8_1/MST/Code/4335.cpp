#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 60;

int n, m, cnt = 0;

char g[N][N];

struct Edge{
	int u, v, w;
	bool operator < (const Edge & T) const {
		return w < T.w;
	}
}edges[100010];

vector<pair<int, int> > points;


int cal(int x, int y){
	return (x - 1) * m + y;
}

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int d[N][N], p[2610];
void bfs(int id){
	auto &[sx, sy] = points[id];
	queue<pair<int, int> > q;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			d[i][j] = -1;
		}
	}
	d[sx][sy] = 0;
	q.push({sx, sy});
	while(q.size()){
		auto &[x, y] = q.front(); q.pop();
		for(int i = 0; i < 4; i ++){
			int nx = x + dx[i], ny = y + dy[i];
			if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && g[nx][ny] != '#' && d[nx][ny] == -1){
				d[nx][ny] = d[x][y] + 1;
				if(g[nx][ny] == 'S' || g[nx][ny] == 'A'){
					edges[++ cnt] = {cal(nx, ny), cal(sx, sy), d[nx][ny]};
				}
				q.push({nx, ny});
			}
		}
	}
}

string s;
int find(int x) {return x == p[x] ? x : p[x] = find(p[x]); }

void solve(){
	cin >> m >> n;
	cnt = 0;
	points.clear();
	getline(cin, s);

	for(int i = 1; i <= n; i ++){
		getline(cin, s);
		s += string(m + 1, ' ');
		for(int j = 0; j < m; j ++){
			g[i][j + 1] = s[j];
			if(s[j] == 'S' || s[j] == 'A'){
				points.push_back({i, j + 1});
			}
		}
	}
	for(int i = 0; i < points.size(); i ++){
		bfs(i);
	}
	sort(edges + 1, edges + cnt + 1);
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			int id = cal(i, j);
			p[id] = id;
		}
	}
	int res = 0;
	for(int i = 1; i <= cnt; i ++){
		auto &[u, v, w] = edges[i];
		if(find(u) != find(v)){
			p[find(u)] = find(v);
			res += w;
		}
	}
	cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 

	int T;
	cin >> T;
	while(T --){
		solve();	
	}
	
	return 0;
}
