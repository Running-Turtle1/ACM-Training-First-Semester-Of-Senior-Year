#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
int st[110];

void solve(){
	cin >> n >> k;
	for(int i = 1; i <= k; i ++){
		int a;
		char b;
		cin >> a >> b;
		if(b == 'F'){
			cout << "No\n";
		}
		else{
			if(st[a]) cout << "No\n";
			else{
				cout << "Yes\n";
				st[a] = 1;
			}
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
