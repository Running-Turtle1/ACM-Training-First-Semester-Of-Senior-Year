#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N = 1e5 + 10;
int a, b, p[N];
int find(int x){
	if(x == p[x]) return x;
	return p[x] = find(p[x]);
}
void solve(){
	bool fg = true;
	while(cin >> a >> b){
		if(a == -1 || b == -1){
			return ;
		}
		if(a == 0 && b == 0){
			for(int i = 1; i <= 100000; i ++){
				p[i] = i;
			}
			cout << (fg ? "Yes" : "No") << '\n';
			fg = false;
		}
		if(find(a) == find(b)) fg = false;
		else p[find(b)] = find(a);
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
