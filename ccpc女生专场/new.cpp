#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;
vector<int> pos[N];

int res[N], n, a[N];

void solve(){
	cin >> n;
	// for(int i = 1; i <= n; i ++){
	// 	pos[i].clear();
    // }

	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		pos[a[i]].push_back(i);
    }	
    set <int> s;
    for(int i=1;i<=n;i++) {
    	s.insert(i);
    }
    for(int i = 1; i <= n; i ++){
    	if(*s.begin() < a[i]) {
    		cout << "-1";
    		return ;
    	}
    	s.erase(a[i]);
    }

    int now = 1;
    for(int i = 1; i <= n; i ++){
    	sort(pos[i].begin(), pos[i].end(), [&] (int a, int b){
    		return a > b;
    	});
    	for(auto &p : pos[i]) {
    		res[p] = now ++;
    	}
    }
    for(int i = 1; i <= n; i ++){
    	cout << res[i] << ' ';
    }
    cout << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	// int t;
	// cin>>t;
	// while(t--)
	solve();
	return 0;
}
