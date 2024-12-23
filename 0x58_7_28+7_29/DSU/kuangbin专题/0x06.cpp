#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;

struct Query{
	int l, r, tp;
}q[5100];


unordered_map<int, int> p, d;
int find(int x, unordered_map<int, int> &mp){
	if(x == mp[x]) return x;
	return mp[x] = find(mp[x], mp);
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= m; i ++){
		int l, r;
		string s;
		cin >> l >> r >> s;
		l --;
		q[i] = {l, r, s == "odd" ? 1 : 0};
		p[l] = l;
		p[r] = r;
		d[l] = 0;
		d[r] = 0;
    }	
    for(int i = 1; i <= m; i ++){
    	auto& [l, r, tp] = q[i];
    	int pl = find(l, p), pr = find(r, p);
    	if(pl == pr){
    		if(((d[r] - d[l]) % 2 + 2) % 2 != tp){
    			cout << i - 1 << '\n';
    			return ;
    		}
    	}
    	else{
    		p[pr] = pl;
    		d[pr] = ((d[r] + tp - d[l]) % 2 + 2) % 2;
    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
