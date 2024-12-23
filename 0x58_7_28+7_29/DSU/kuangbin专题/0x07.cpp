#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int p[2100], d[2100];

int find(int x){
	if(x == p[x]) return x;
	int t = find(p[x]);
	(d[x] += d[p[x]]) %= 2;
	return p[x] = t;
}

void solve(int yyy){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		p[i] = i;
		d[i] = 0;
    }
    bool fg = false;
    while(m --){
    	int a, b;
    	cin >> a >> b;
    	int pa = find(a), pb = find(b);
    	if(pa != pb){
    		p[pb] = pa;
    		d[pb] = ((1 + d[a] - d[b]) % 2 + 2) % 2;
    	}
    	else{
    		if(((d[a] - d[b]) % 2 + 2) % 2 != 1){
    			fg = true;
    		}
    	}
    }
    cout << "Scenario #"<<yyy<<":\n";
    cout << (fg ? "Suspicious bugs found!" : "No suspicious bugs found!") << '\n';
    cout << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	for(int i = 1; i <= T; i ++){
		solve(i);
	}

	return 0;
}