#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int p[2100]; // 1 ~ n : 朋友域 ; n+1 ~ 2n 敌人域

int find(int x){
	if(x == p[x]) return x;
	return p[x] = find(p[x]);
}

void merge(int x, int y){
	p[find(y)] = find(x);
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n * 2; i ++){
		p[i] = i;	
    }
    for(int i = 1; i <= m; i ++){
    	string opt;
    	int x, y;
    	cin >> opt >> x >> y;
    	if(opt == "F"){
    		merge(x, y);
    	}
    	else{
    		merge(x, y + n);
    		merge(y, x + n);
    	}
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	res += p[i] == i;
    }
    cout << res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}