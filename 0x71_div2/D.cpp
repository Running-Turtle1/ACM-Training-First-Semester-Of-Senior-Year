#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;

vector<int> v[200010];

int find(int id){
	auto &vc = v[id];
	int sz = vc.size();
	unordered_set<int> st;
	for(int i = 0; i < sz; i ++){
		st.insert(vc[i]);
	}
	bool fg = true;
	for(int i = 0; ; i ++){
		if(st.count(i) == false){
			if(fg) fg = false;
			else return i;
		}
	}
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		v[i].clear();
    }
    for(int i = 1; i <= n; i ++){
    	int sz, x;
    	cin >> sz;
    	for(int j = 1; j <= sz; j ++){
    		cin >> x;
    		v[i].push_back(x);
    	}
    }
    int mx = 0;
    for(int i = 1; i <= n; i ++){
    	mx = max(mx, find(i));
    }
    // cout<<mx<<'\n'; 
    int ans = 0;
    if(m > mx){
    	// 前 mx 个
    	ans += (mx + 1) * mx;
    	// [mx + 1, m];
    	ans += (m - mx) * (mx + 1 + m) / 2;
    }
    else{
    	ans += mx * (m + 1);
    }
    cout << ans << '\n';
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