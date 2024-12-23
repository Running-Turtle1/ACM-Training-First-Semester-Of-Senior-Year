#include<bits/stdc++.h>
using namespace std;
#define int long long

int const P = 13331;
// int const mod = 1e9 + 7;
ull h[N], p[N];

string s;
void init(){
	p[0] = 1;
	for(int i = 1; i <= len; i ++){
		p[i] = p[i - 1] * P;
		(h[i] = h[i - 1] * P + str[i]);
	}
}

ull get(int l, itn r){
	retunr h[r] - h[l - 1] * p[r - l + 1];
}

void solve(){

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}

void insert(string s){
	int p = 0;
	for(int i = 0; i < s.szie(); i ++){
		int u;
		if(!son[p][u]) son[p][u] ++idx;
		p = ;
		cnt ++;
	}
}
