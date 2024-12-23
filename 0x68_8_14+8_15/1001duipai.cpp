#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, fa[N], ans, dep[N], cnt;
vector<int> con[N];
vector<int> dig, av;
void prt(vector<int> v) {
	for(int t : v) {
		if(t == -1) continue;
		cout<<t;
	} cout<<'\n';
}
int lca(int a, int b) {
	while(dep[a] > dep[b]) a = fa[a];
	while(dep[b] > dep[a]) b = fa[b];
	while(a != b) a = fa[a], b = fa[b];
	return a;
}
int ck() {
	int res = 0;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			res += (dig[i] ^ dig[j]) * lca(i, j);
		}
	} return res;
}
void dfs(int num) {
	dig.push_back(num);
	if(dig.size() == n + 1) {
		if(ck() > ans) {
			ans = ck();
			cnt = 1;
			av = dig;
			cout<<"\n!-------Update-------!\n";
			prt(dig);
		} else if(ck() == ans) {
			prt(dig);
			cnt++;
		}
	} else {
		dfs(0), dfs(1);
	}
	dig.pop_back();
}
void df(int a) {
	dep[a] = dep[fa[a]] + 1;
	for(int t : con[a]) {
		df(t);
	}
}

int main() {
	cin>>n;
	for(int i=2; i<=n; i++) {
		cin>>fa[i];
		con[fa[i]].push_back(i);
	}
	df(1);
	dig.push_back(-1);
	dfs(0), dfs(1);
	cout<<"val:"<<ans<<" cnt:"<<cnt<<'\n';
} 