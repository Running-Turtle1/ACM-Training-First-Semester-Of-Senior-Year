#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int x = 6;
	int s = 0;
	int tmp = 0;
		for(int i = 0; i < 4; i ++){
			cout << i << ' ' << (n >> i & 1) << ' ' << (x >> s & 1) << '\n';
			if(n >> i & 1){
				if(x >> s & 1)  tmp += (1LL << i);
				s ++;
			} 
		}
		x = tmp;
		cout << x <<' ' << tmp << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
