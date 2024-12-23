#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

vector<pair<int, int> > e[N];
int diameter = 0;
// 返回从 u 点往下走的最大长度
int dfsForLongestPath(int u, int fa){
	// 从 u 往下走的最大长度和次大长度
	int d1 = 0, d2 = 0;
	for(auto& [v, w] : e[u]){
		if(v == fa) continue;
		int d = dfsForLongestPath(v, u) + w;
		if(d >= d1) d2 = d1, d1 = d;
		else if(d > d2) d2 = d;
	}
	diameter = max(diameter, d1 + d2);
	return d1;
}

int n, res = 0;

void solve(){
	cin >> n;
	for(int i = 1; i < n; i ++){
		int a, b, c;
		cin >> a >> b >> c;
		e[a].push_back({b, c});
		e[b].push_back({a, c});
		res += 2 * c;
    }
    dfsForLongestPath(1, 0);
    // cout << diameter << '\n';
    cout << res - diameter;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
