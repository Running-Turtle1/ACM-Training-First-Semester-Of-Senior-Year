#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

int n;
int v[N], d[N];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		d[i] = 0;
    }
    for(int i = 1; i < n; i ++){
    	int u, v;
    	cin >> u >> v;
    	d[u] ++; 
    	d[v] ++;
    }
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i ++){
    	v[i + 1] = (s[i] == '0' ? 0 : (s[i] == '1' ? 1 : 2));
    }
    int x, y, z;
    x = y = z = 0;

    int t = 0;

    for(int i = 1; i <= n; i ++){
    	if(d[i] == 1 && i != 1){ 
    		if(v[i] == 0) x ++;
    		if(v[i] == 1) y ++;
    		if(v[i] == 2) z ++;
    	}
    	else if(v[i] == 2 && i != 1){
    		t ++;
    	}
    }
    // cout << x << ' ' << y << ' ' << z << ' ' << t << '\n';
    if(v[1] == 0){ // 抢 1
    	cout << y + (z + 1) / 2 << '\n';
    }
    else if(v[1] == 1){ // 抢 0
    	cout << x + (z + 1) / 2 << '\n';
    }
    else if(x == y) { // 可能需要中间缓冲
    	if(t & 1){
    		cout << x + (z + 1) / 2 << '\n';
    	}
    	else{
    		cout << x + z / 2 << '\n';
    	}
    }
    else if(x > y){
    	cout << x + z / 2 << '\n';
    }
    else{
    	cout << y + z / 2 << '\n';
    }
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