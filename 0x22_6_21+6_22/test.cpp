#include<bits/stdc++.h>
using namespace std;
#define int long long

string t1 = "??";
int k = 2;

void dfs(int u){
	if(u == k){
		string t2 = t1;
		cout << t1 << '\n';
		reverse(t2.begin(), t2.end());
		// res += (t1 != t2);
		return ;
	}
	if(t1[u] == 'A' || t1[u] == 'B'){
		dfs(u + 1);
	}
	else{
		t1[u] = 'A';
		dfs(u + 1);
		t1[u] = '?';

		t1[u] = 'B';
		dfs(u + 1);
		t1[u] = '?';
	}
}

void solve(){
	dfs(0);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
