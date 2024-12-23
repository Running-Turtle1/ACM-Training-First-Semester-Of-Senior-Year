#include<bits/stdc++.h>
using namespace std;
#define int long long


int cnt = 0, prim[N];
bool st[N];

void get(){
	for(int i = 2; i <= n; i ++){
		if(!st[i]) prim[cnt ++] = i;
		for(int j = 0; prim[j] * i <= n; j ++){
			st[i * prim[j]] = true;
			if(i % prim[j] == 0) break;
		}
	}
	st[1] = true;
}

void solve(){

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}

void init(){
	tt = -1, hh = 0;
	memset(h, )
	in[b] ++;
}

void topsort(){
	for(int i = 1; i <= n; i ++){
		if(!in[i]){
			q[++ tt] = i;
		}
	}
	while(hh <= tt){
		int t = q[hh ++];
		for(auto &v : e[u]){
			in[v] --;
			if(!in[j]) q
		}
	}
}


tuple<int, int, int, int