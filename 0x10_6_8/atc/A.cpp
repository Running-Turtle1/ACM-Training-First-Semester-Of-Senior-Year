#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int a[110];

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    a[n + 1] = 2e9;
    for(int i = 1; i <= n + 1; i ++){
    	if(m < a[i]){
    		cout << i - 1 << '\n';
    		return ;
    	}
    	m -= a[i];
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}