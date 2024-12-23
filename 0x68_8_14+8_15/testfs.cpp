#include<bits/stdc++.h>
using namespace std;
int k, a[3];
bool oka, okb;
void dfs(int hp, int cho, int dep) {
	hp -= a[cho];
	if(hp <= 0) {
		if(dep % 2) oka = true;
		else okb = true;
	} else {
		dfs(hp, 0, dep+1);
		dfs(hp, 1, dep+1);
	}
}
int main() {
	int T;
	cin>>T;
	while(T--) {
		cin>>k>>a[0]>>a[1];
		oka = okb = false;
		dfs(k, 0, 1);
		dfs(k, 1, 1);
		cout<<oka<<' '<<okb<<'\n';
	}
}