#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, a[N], v[N];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    string s;
    cin >> s;
    s = ' ' + s;
    int now = 0;
    int l = 1, r = n;
    while(l <= r){
    	int tl = l, tr = r;
    	while(l <= r && s[l] != 'L'){
    		l ++;
    	}
    	while(l <= r && s[r] != 'R'){
    		r --;
    	}
    	if(l <= r){
    		for(int k = tl; k < l; k ++){
    			v[k] = now;
    		}
    		for(int k = tr; k > r; k --){
    			v[k] = now;
    		}
    		v[l] = now + 1;
    		v[r] = now + 1;
    		now ++;
    		l ++;
    		r --;
    	}
    	else{
    		for(int k = tl; k <= tr; k ++) v[k] = now;
    	}
    	// now ++;
    	// cout << l << ' ' << r << '\n';
    	// v[l ++] = now;
    	// v[r --] = now;
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	// cout << v[i] << " \n"[i == n];
    	res += a[i] * v[i];
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
