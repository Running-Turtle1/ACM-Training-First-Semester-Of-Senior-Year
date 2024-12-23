#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

int n, m;
int p[N]; // (i, j) : (i - 1) * m + j
int sz[N];

char tmp[1000010];

int cal(int x, int y){
	return (x - 1) * m + y;
}

int find(int x){
	if(x == p[x]) return p[x];
	// int fa = find(p[x]);
	// sz[p[x]] += sz[x];
	return p[x] = find(p[x]);
}

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void merge(int a, int b){
	int fa = find(a);
	int fb = find(b);
	if(fa != fb){
		p[fb] = fa;
		sz[fa] += sz[fb];
	}
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n * m; i ++){
		p[i] = i;
		sz[i] = 0;
    }
	char g[n + 10][m + 10];
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		cin >> g[i][j];     
     		if(g[i][j] == '#'){
     			sz[cal(i, j)] = 1;
     		}  
        }
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
        	for(int d = 0; d < 4; d ++){
        		int a = i + dx[d], b = j +dy[d];
        		if(a >= 1 && a <= n && b >= 1 && b <= m && g[i][j] == '#' && g[a][b] == '#'){
        			merge(cal(i, j), cal(a, b));
        			res = max(res, sz[find(cal(i, j))]);
        		}
        	}
        }
    }

    cout << res << '\n';

    // vector<pair<int,int> > op1; // 表示 sz[fs] += sc 应该取消
    // vector<int> q; // 表示 i 应该指向自己
    // 操作 row
    // for(int i = 1; i <= n; i ++){
    // 	for(int j = 1; j <= m; j ++){
    // 		if(g[i][j] == '.'){
    // 			sz[cal(i, j)] = 1;
    // 			res = max(res, 1LL);
    // 		}
    // 	}
    // 	for(int j = 1; j <= m; j ++){
    // 		if(g[i][j] == '.'){
    // 			for(int d = 0; d < 4; d ++){
    //     			int a = i + dx[d], b = j + dy[d];
    //     			if(a >= 1 && a <= n && b >= 1 && b <= m && (g[a][b] == '#' || a == i)){
    //     				int fa = find(cal(a, b));
    //     				int fb = find(cal(i, j));
    //     				if(fa != fb){
    //     					p[fa] = fb;
    //     					sz[fb] += sz[fa];
    //     					res = max(res, sz[fb]);
    //     					op1.push_back({fb, sz[fa]});
    //     					q.push_back(fa);
    //     				}
    //     				// merge(cal(i, j), cal(a, b));
    //     				// res = max(res, sz[find(cal(i, j))]);
    //     			}
    //     		}
    // 		}
    // 	}
    // 	while(op1.size()){
    // 		auto &[fs,sc]=op1.back();
    // 		sz[fs]-=sc;
    // 		op1.pop_back();
    // 	}
    // 	while(q.size()){
    // 		p[i]=i;
    // 		q.pop_back();
    // 	}
    // 	for(int j = 1; j <= m; j ++){
    // 		if(g[i][j] == '.'){
    // 			sz[cal(i, j)] = 0;
    // 		}
    // 	}
    // }
    vector<pair<int,int> > op1; // 表示 sz[fs] += sc 应该取消
    vector<int> q; // 表示 i 应该指向自己
    for(int i = 1; i <= n; i ++){
    	for(int j = 1; j <= m; j ++){
    		if(g[i][j] == '.'){
    			sz[cal(i, j)] = 1;
    			res = max(res, 1LL);
    		}
    	}
    }
    cout << res << '\n';
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