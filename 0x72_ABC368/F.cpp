#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n;

int a[N];
int f[N]; 

int sg(int x){
	if(f[x] != -1) return f[x];
	unordered_set<int> q;
	for(int i = 1; i <= x / i; i ++){
		if(x % i == 0){
			if(x / i != x) q.insert(sg(x / i));
			if(i != x) q.insert(sg(i));
		}
	}
	for(int i = 0; ; i ++){
		if(!q.count(i)) return f[x] = i;
	}
}

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    memset(f, -1, sizeof f);
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	res ^= sg(a[i]);
    }

    cout << (res ? "Anna" : "Bruno") << '\n';
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}