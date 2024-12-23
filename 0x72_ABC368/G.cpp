#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, q, a[N], b[N];

int tr[N];

void add(int p, int v){
	for(int i = p; i < N; i += i & -i){
		tr[i] += v;
	}
}

int ask(int p){
	int res = 0;
	for(int i = p; i; i -= i & -i){
		res += tr[i];
	}
	return res;
}

int ask(int l, int r){
	if(l > r) return 0;
	return ask(r) - ask(l - 1);
}

set<int> pos;

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		add(i, a[i]);
    }
    for(int i = 1; i <= n; i ++){
    	cin >> b[i];
    	if(b[i] > 1){
    		pos.insert(i);
    	}
    }
    cin >> q;
    while(q --){
    	int opt, l, r;
    	cin >> opt >> l >> r;
    	if(opt == 1){
    		add(l, r - a[l]);
    		a[l] = r;
    	}
    	else if(opt == 2){
    		if(r == b[l]) continue ;
    		if(b[l] == 1){ // 1 变非 1
    			pos.insert(l);
    		}
    		if(r == 1){
    			pos.erase(l);
    		}
    		b[l] = r;
    	}
    	else{
    		int res = a[l];
    		if(l != r){
    			l ++;
    			vector<int> p;
    			auto it = pos.lower_bound(l);
    			if(it != pos.end()){
    				while((*it) <= r && it != pos.end()){
    					p.push_back(*it);
    					it ++;
    				}
    			}	
    			// cout << "Pos: \n";
    			// for(auto &ps : p) cout << ps << ' '; cout << '\n';
    			if(p.size() == 0){
    				res += ask(l, r);
    			}
    			else{
    				res += ask(l, p[0] - 1);
    				res = max(res * b[p[0]], res + a[p[0]]);
    				// res *= b[p[0]];
    				for(int i = 0; i + 1 < p.size(); i ++){
						res += ask(p[i] + 1, p[i + 1] - 1);
						res = max(res * b[p[i + 1]], res + a[p[i + 1]]);
						// res *= b[p[i + 1]];
					}
    				res += ask(p.back() + 1, r);
    			}
    		}
    		cout << res << '\n';
    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
