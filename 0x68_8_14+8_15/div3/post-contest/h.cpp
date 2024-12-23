#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, m, a[N];

struct info{
	int len, l, r;
	bool operator < (const info & T) const {
		if(len != T.len) return len < T.len;
		return l < T.l;
	}
};

set<int> v;
set<info> infos;

void solve(){
	v.clear();
    infos.clear();
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
	}
	a[++ n] = 0;
	a[++ n] = 1e17;
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i ++){
    	v.insert(a[i]);
    }
	for(int i = 1; i < n; i ++){
		if(a[i + 1] !=  a[i] + 1){
			infos.insert({a[i + 1] - a[i] - 1, a[i] + 1, a[i + 1] - 1});
			// cout << a[i + 1] - a[i] - 1 << '\n';
		}
    }
    int m;
    cin >> m; 
    auto ins = [&] (int l, int r) -> void {
    	if(l <= r) {
    		infos.insert({r - l + 1, l, r});
    	}
    };
    auto del = [&] (int l, int r) -> void {
    	if(l <= r){
    		infos.erase({r - l + 1, l, r});
    	}
    };
    while(m --){
    	char opt;
    	int x;
    	cin >> opt >> x;
    	switch(opt) {
    		case '+' : { // 加入 x
    			auto r = v.upper_bound(x);
    			auto l = prev(r);
    			int vr = *r, vl = *l;
    			// old : l + 1 ~ r - 1
    			// num : vl ~ x ; x ~ vr
    			// seg : vl + 1 ~ x - 1 ; x + 1 ~ vr - 1
    			v.insert(x);
    			del(vl + 1, vr - 1);
    			ins(vl + 1, x - 1);
    			ins(x + 1, vr - 1);
    			break;
    		}
    		case '-' : { // 删除 x
    			v.erase(x);
    			auto r = v.upper_bound(x);
    			auto l = prev(r);
    			int vr = *r, vl = *l;
    			del(vl + 1, x - 1);
    			del(x + 1, vr - 1);
    			ins(vl + 1, vr - 1);
    			break;
    		}
    		case '?' : { // 要找 l 最小的 and len >= x 的
    			auto it = infos.lower_bound({x, -1, -1});
    			int ans = 2e9;
    			while(it != infos.end()){
    				ans = min(ans, it->l);
    				it = next(it);
    			}
    			cout << ans << ' ';
    			// cout << it->len << '\n';
    			// cout << it->l << ' ';
    			// cout << it->l << ' ' << it->r << '\n';
    			break;
    		} 
    	}
    }
    cout << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}