#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(int n){
	int q;
	cin >> q;

	vector<int> a(n);
	for(int i = 0; i < n; i ++){
		cin >> a[i];
    }

    vector<pair<int, int> > seg;
    for(int i = 0; i < n; i ++){
    	int j = i;
    	while(j < n && a[j] == a[i]) j ++;
    	seg.push_back({i, j - 1});
    	i = j - 1;
    }

    int sz = __lg(seg.size()) + 3;
    vector<vector<int> > f(seg.size(), vector<int> (sz, 0));
    for(int i = 0; i < seg.size(); i ++){
    	f[i][0] = seg[i].second - seg[i].first + 1;
    }
    for(int j = 1; j < sz; j ++){
    	for(int i = 0; i + (1 << j) - 1 < seg.size(); i ++){
    		f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    	}
    }

    auto askMax = [&] (int l, int r) {
    	int s = __lg(r - l + 1);
    	return max(f[l][s], f[r - (1 << s) + 1][s]);
    };
 
    auto find = [&] (int p) {
    	int l = 0, r = seg.size() - 1;
    	while(l < r){
    		int mid = l + r + 1 >> 1;
    		if(p >= seg[mid].first) l = mid;
    		else r = mid - 1;
    	}
    	return l;
    };

    while(q --){
    	int l, r;
    	cin >> l >> r;
    	-- l, -- r;

    	int pl = find(l), pr = find(r);
    	// cout << "pos: " << pl << ' ' <<pr << '\n';
    	if(pl == pr){
    		cout << r - l + 1 << '\n';
    		continue ;
    	}
    	else if(pr == pl + 1){
    		cout << max(seg[pl].second - l + 1, r - seg[pr].first + 1) << '\n';
    	}
    	else{
    		int mx = askMax(pl + 1, pr - 1);	
    		cout << max({mx, seg[pl].second - l + 1, r - seg[pr].first + 1}) << '\n';
    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 

	int n;
	while(cin >> n, n){
		solve(n);	
	}
	
	return 0;
}
