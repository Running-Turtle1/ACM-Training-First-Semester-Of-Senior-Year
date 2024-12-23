#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e4 + 10;

int n;
vector<int> goods[N];

void solve(){
	for(int i = 1; i <= 10000; i ++){
		goods[i].clear();
	}
	for(int i = 1; i <= n; i ++){
		int p, d;
		cin >> p >> d;
		goods[d].push_back(p);
	}
	int ans = 0;
	priority_queue<int> q;
	for(int i = 10000; i >= 1; i --){
		if(goods[i].size() == 0) continue ;
		for(auto &p : goods[i]){
			q.push(p);
		}
		ans += q.top();
		q.pop();
	}
	cout << ans << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 

	while(cin >> n){
		solve();
	}

	return 0;
}
