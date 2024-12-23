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


// 维护每个数字最后一次出现的位置
map<int, int> cnt; // 维护数字出现次数
set<pair<int, int> > st; // cnt[x] = 1 {pos, x}
vector<int> pos[N];

void solve(){
	set<int> has;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		pos[i].clear();
    }
    cnt.clear();
    st.clear();
    
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		cnt[a[i]] ++;
		pos[a[i]].push_back(i);
    }
    for(auto &[x, y] : cnt){
    	if(y == 1){
    		st.insert({pos[x][0], x});
    	}
    }

    buildMax(1, 1, n);  // 建立最大值线段树
    buildMin(1, 1, n);  // 建立最小值线段树
 
    int wpc = 0;
    vector<int> res;
    for(int i = 1, j=1; i <= n; i ++,j++){
    	int p = -1;
    	if(st.size()) p = (*st.lower_bound({i, -1})).first;
    	else p = n;

    	if(p < i) p = n;

    	if(wpc) cout << i << ' ' <<p << '\n';

    	// i 到 p 里面选择一个数
    	if(j & 1){ // 此时选择最大值
    		// seg 查找一个没被考虑过的最大值
    		int mx = askMax(1, i, p);
    		if(mx == -2e9) break;
    		int maxPos = *lower_bound(pos[mx].begin(), pos[mx].end(), i);// - pos[mx].begin();
    		if(wpc)cout << mx << '\n';
    		if(wpc) cout << maxPos<<'\n';
    		for(auto &p : pos[mx]){
    			// cout << "P: " << p << '\n';
    			changeMax(1, p, -2e9);
    			changeMin(1, p, 2e9);
    			// cout<<askMax(1,p,p)<<'\n';
    		}
    		res.push_back(mx);
    		// has.insert(mx);
    		for(int j = i; j <= maxPos; j ++){
    			cnt[a[j]] --;
    			if(cnt[a[j]] == 1){
    				st.insert({j, a[j]});
    			}
    		}
    		i = maxPos;
    	}
    	else{
    		int mn = askMin(1, i, p);
    		if(mn == 2e9){
    			// cout<<"wpc\n";
    			break;
    		}
    		int minPos = *lower_bound(pos[mn].begin(), pos[mn].end(), i);// - pos[mn].begin();

    		if(wpc) cout << mn << '\n';
    		if(wpc) cout << minPos<<'\n';
    		for(auto &p : pos[mn]) {
    			changeMax(1, p, -2e9);
    			changeMin(1, p, 2e9);
    		}
    		res.push_back(mn);
    		// has.insert(mn);
    		for(int j = i; j <= minPos; j ++){
    			cnt[a[j]] --;
    			if(cnt[a[j]] == 1){
    				st.insert({j, a[j]});
    			}
    		}
    		i = minPos;
    	}
    }
    cout << res.size() << '\n';
    for(auto &p : res){
    	cout << p << ' ';
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