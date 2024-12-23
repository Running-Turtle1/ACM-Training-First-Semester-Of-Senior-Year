#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 3e5 + 10;

int n, a[N];
          
#define lc u << 1
#define rc u << 1 | 1

struct TreeMax {
    int l, r;
    int mx;
} trMax[N << 2];

struct TreeMin {
    int l, r;
    int mn;
} trMin[N << 2];


// 最大值线段树的pushup
void pushupMax(int u) {
    trMax[u].mx = max(trMax[lc].mx, trMax[rc].mx);
}

// 最小值线段树的pushup
void pushupMin(int u) {
    trMin[u].mn = min(trMin[lc].mn, trMin[rc].mn);
}

// 最大值线段树的build
void buildMax(int u, int l, int r) {
    trMax[u] = {l, r, a[l]};
    if (l == r) return;
    int mid = (l + r) >> 1;
    buildMax(lc, l, mid);
    buildMax(rc, mid + 1, r);
    pushupMax(u);
}

// 最小值线段树的build
void buildMin(int u, int l, int r) {
    trMin[u] = {l, r, a[l]};
    if (l == r) return;
    int mid = (l + r) >> 1;
    buildMin(lc, l, mid);
    buildMin(rc, mid + 1, r);
    pushupMin(u);
}

// 最大值线段树的change
void changeMax(int u, int p, int val) {
    if (trMax[u].l == trMax[u].r) {
        trMax[u].mx = val;
        return;
    }
    int mid = (trMax[u].l + trMax[u].r) >> 1;
    if (p <= mid) changeMax(lc, p, val);
    else changeMax(rc, p, val);
    pushupMax(u);
}

// 最小值线段树的change
void changeMin(int u, int p, int val) {
    if (trMin[u].l == trMin[u].r) {
        trMin[u].mn = val;
        return;
    }
    int mid = (trMin[u].l + trMin[u].r) >> 1;
    if (p <= mid) changeMin(lc, p, val);
    else changeMin(rc, p, val);
    pushupMin(u);
}

// 最大值线段树的查询
int askMax(int u, int l, int r) {
    if (l <= trMax[u].l && r >= trMax[u].r) {
        return trMax[u].mx;
    }
    int mid = (trMax[u].l + trMax[u].r) >> 1;
    int res = LLONG_MIN;
    if (l <= mid) res = max(res, askMax(lc, l, r));
    if (r > mid) res = max(res, askMax(rc, l, r));
    return res;
}

// 最小值线段树的查询
int askMin(int u, int l, int r) {
    if (l <= trMin[u].l && r >= trMin[u].r) {
        return trMin[u].mn;
    }
    int mid = (trMin[u].l + trMin[u].r) >> 1;
    int res = LLONG_MAX;
    if (l <= mid) res = min(res, askMin(lc, l, r));
    if (r > mid) res = min(res, askMin(rc, l, r));
    return res;
}

set<int> edPos; // 每个可选数最后出现的 {位置, 数}
vector<int> pos[N];

void solve(){
	edPos.clear();
	set<int> tmp;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		pos[i].clear();
    }
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		pos[a[i]].push_back(i);
    }
    for(int i = n; i >= 1; i --){
    	if(tmp.count(a[i]) == false){
    		edPos.insert(i);
    	}
    	tmp.insert(a[i]);
    }
    int debug = 0;
    if(debug){
    	for(auto &ps : edPos) cout << ps << ' ';
    	cout << '\n';
    }
    buildMax(1, 1, n);
    buildMin(1, 1, n);
    vector<int> res;

    for(int i = 1, cnt = 1; i <= n; i ++, cnt ++){
    	if(edPos.size() == 0) break;
    	int p = *edPos.lower_bound(i);
    	if(debug) cout << i << ' ' << p << '\n';
    	if(cnt & 1){
    		int mx = askMax(1, i, p);
    		i = *lower_bound(pos[mx].begin(), pos[mx].end(), i);
    		res.push_back(mx);
    		for(auto &ps : pos[mx]){
    			changeMax(1, ps, -2e9);
    			changeMin(1, ps, 2e9);
    			if(edPos.count(ps)) edPos.erase(ps);
    		}
    	}
    	else{
    		int mn = askMin(1, i, p);
    		i = *lower_bound(pos[mn].begin(), pos[mn].end(), i);
    		res.push_back(mn);
    		for(auto &ps : pos[mn]){
    			changeMax(1, ps, -2e9);
    			changeMin(1, ps, 2e9);
    			if(edPos.count(ps)) edPos.erase(ps);
    		}
    	}
    	if(debug){
    		cout << "choose: " << res.back() << '\n';
    	}
    }
    cout << res.size() << '\n';
    for(auto &i : res) cout << i << ' ';
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