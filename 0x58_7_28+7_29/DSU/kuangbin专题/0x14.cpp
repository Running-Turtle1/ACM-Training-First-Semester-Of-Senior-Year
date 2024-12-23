#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, p1, p2;

struct info{
	int x, y, dis;
}infos[1100];

int p[610], d[610]; 

int find(int x){
	if(x == p[x]) return x;
	int t = find(p[x]);
	d[x] = (d[x] + d[p[x]]) % 2;
	return p[x] = t;
}

pair<int, int> bk[610]; // 每个连通块的 0 1 数量
vector<int> same[610];
vector<int> dif[610];
map<int, int> mp;
int cnt = 0;

void solve(){
	n = p1 + p2;
	cnt = 0;
	mp.clear();
	for(int i = 1; i <= n; i ++){
		p[i] = i;
		d[i] = 0;
		bk[i] = {0, 0};
		same[i].clear();
		dif[i].clear();
	}
	for(int i = 1; i <= m; i ++){
		int x, y;
		string s;
		cin >> x >> y >> s;
		infos[i] = {x, y, s == "no"};
		// cout << x << ' ' << y << ' ' << (s == "no") << '\n';
	}

	for(int i = 1; i <= m; i ++){
		auto &[x, y, tp] = infos[i];
		if(x == y) continue ;
		int px = find(x), py = find(y);
		if(px != py){
			p[py] = px;
			d[py] = ((d[x] - tp - d[y]) % 2 + 2) % 2;
		}
	}

	// cout << find(1) << ' ' << find(2) << '\n';
	// cout << d[1] << ' ' << d[2] << '\n';

	for(int i = 1; i <= n; i ++){
		if(find(i) == i){
			mp[i] = ++ cnt;
		}

		int pi = find(i);

		if(d[i] == 0){
			bk[mp[pi]].first ++;
			same[mp[pi]].push_back(i);
		}
		else{
			bk[mp[pi]].second ++;
			dif[mp[pi]].push_back(i);
		}
	}

	// f[i][j] 表示考虑到第 i 个连通块, 划分出来 p1 个天使的方案数
	vector<vector<int> > f(cnt + 1, vector<int> (p1 + 1, 0));
	f[0][0] = 1;
	f[1][bk[1].first] ++ ;
	f[1][bk[1].second] ++ ;
	for(int i = 1; i < cnt; i ++){
		int fs = bk[i + 1].first, sc = bk[i + 1].second;
		for(int j = 0; j <= p1; j ++){
			if(f[i][j]){
				if(j + fs <= p1){
					f[i + 1][j + fs] += f[i][j];
					if(f[i + 1][j + fs] > 1e9) f[i + 1][j + fs] = 1e9;
				}
				if(j + sc <= p1){
					f[i + 1][j + sc] += f[i][j];
					if(f[i + 1][j + sc] > 1e9) f[i + 1][j + sc] = 1e9;
				}
			}
		}
	}
 	
//  	cout << cnt << '\n';
// 	for(int i = 1; i <= cnt; i ++){
// 		cout << bk[i].first << ' ' << bk[i].second << '\n';
// 	}
	// cout << f[cnt][p1] << '\n';

	if(f[cnt][p1] == 1){
		vector<int> choose;
		int now = p1;
		for(int i = cnt; i >= 1; i --){
			int fs = bk[i].first, sc = bk[i].second;
			if(f[i - 1][now - fs] == 1){
				now -= fs;
				// cout << fs << '\n';
				choose.push_back(fs);
			}
			else{
				now -= sc;
				// cout << sc << '\n';
				choose.push_back(sc);
			}
		}
		vector<int> res;
		for(int i = 1; i <= cnt; i ++){
			int t = choose[cnt - i];
			if(bk[i].first == t){
				for(int j = 0; j < same[i].size(); j ++){
					res.push_back(same[i][j]);
				}
			}
			else{
				for(int j = 0; j < dif[i].size(); j ++){
					res.push_back(dif[i][j]);
				}
			}
		}
		sort(res.begin(), res.end());
		for(auto &x : res) cout << x << '\n';
		cout << "end\n";
	}
	else{
		cout << "no\n";
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	
	while(cin >> m >> p1 >> p2, m || p1 || p2){
		solve();
	}

	return 0;
}
// 要求唯一确定每个居民的身份
// f[i][j] 表示考虑到第 i 个并查集, 得到 j 个天使的方案数
 