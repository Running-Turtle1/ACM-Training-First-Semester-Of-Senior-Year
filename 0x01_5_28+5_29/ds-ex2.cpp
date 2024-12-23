#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
int const N = 5e4 + 10;
int p[N * 3];

int find(int x){
	if(x == p[x]) return x;
	return p[x] = find(p[x]);
}

void merge(int x, int y){
	p[find(x)] = find(y);
}

void solve(){
	cin >> n >> k;
	for(int i = 1; i <= 3 * n; i ++){
		p[i] = i;
    }
    int res = 0;
    for(int i = 1; i <= k; i ++){
    	int opt, x, y;
    	cin >> opt >> x >> y;
    	if(x > n || y > n){
    		res ++;
    	}
    	else if(opt == 1){
    		// x 与 y 不能互吃
    		if(find(x) == find(y + n) || find(x) == find(y + 2*n)) res ++;
    		else{
    			merge(x, y);
    			merge(x + n, y + n);
    			merge(x + 2 * n, y + 2 * n);
    		}
    	}
    	else{
    		if(x == y) res ++;
    		else if(find(x) == find(y) || find(x) == find(y + n)) res ++;  
			else{
				merge(x, y + 2 * n);
    			merge(y, x + n);
    			merge(x + 2 * n, y + n); // x 天敌被 y 捕食
			}
    	}
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
