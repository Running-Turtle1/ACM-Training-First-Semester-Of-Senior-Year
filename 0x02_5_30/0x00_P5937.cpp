#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

int n, m;
int p[N], d[N];
pair<int, int> ask[N];
int tmp[N];
string opt[N];

int find(int x){
	if(x == p[x]) return x;
	int t = find(p[x]);
	d[x] = (d[x] + d[p[x]]) % 2;
	return p[x] = t;
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= m; i ++){
		int x, y;
		cin >> x >> y >> opt[i];
		ask[i] = {x, y};
		tmp[2 * i - 1] = x;
		tmp[2 * i] = y;
    }
    sort(tmp + 1, tmp + 2 * m + 1);
    int sz = unique(tmp + 1, tmp + 2 * m + 1) - tmp - 1;
    for(int i = 1; i <= m; i ++){
    	ask[i].first = lower_bound(tmp + 1, tmp + sz + 1, ask[i].first-1) - tmp;
    	ask[i].second = lower_bound(tmp + 1, tmp + sz + 1, ask[i].second) - tmp;
    }
    for(int i = 1; i <= sz; i ++){
    	p[i] = i;
    	d[i] = 0;
    }
    for(int i = 1; i <= m; i ++){
    	auto &[l, r] = ask[i];
    	int pl = find(l), pr = find(r);
    	if(pl != pr){
    		p[pl] = pr;
    		if(opt[i] == "odd"){
    			d[pl] = (d[r] - d[l] + 1 + 2) % 2;
    		}
    		else{
    			d[pl] = (d[r] - d[l] + 2) % 2;
    		}
    	}
    	else{
    		if(opt[i] == "odd"){
    			if((d[r] - d[l] + 2) % 2 == 0){
    				cout << i - 1;
    				return ;
    			}
    		}
    		else{
    			if((d[r] - d[l] + 2) % 2 == 1){
    				cout << i - 1;
    				return ;
    			}
    		}
    	}
    }
    cout<<m;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}