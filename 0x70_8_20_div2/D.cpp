#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1

int const N = 3e5 + 10;

struct tree{
	int l, r;
	int mn, mx;
}tr[N][2];


int n, a[N];

void pushup(int u, int id){
	if(id == 0){
		tr[u][0].mx = max(tr[lc][0].mx, tr[rc][0].mx);
	}
	else{
		tr[u][1].mn = min(tr[lc][1].mn, tr[rc][1].mn);
	}
}

void build(int u, int l, int r, int id){
	tr[u][id] = {l, r, a[l], a[l]};
	if(l == r) return ;
	int mid = l + r >> 1;
	build(lc, l, mid, id);
	build(rc, mid + 1, r, id);
	pushup(u, id);
}

void change(int u, int p, int val, int id){
	if(tr[u][id].l == tr[u][id].r){
		tr[u][id] = {p, p, val};
		return ;
	}
	int mid = tr[u][id].l + tr[u][id].r >> 1;
	if(p <= mid) change(lc, p, val, id);
	else change(rc, p, val, id);
	pushup(u, id);
}

int askVal(int u, int l, int r, int id){
	if(l <= tr[u][id].l && r >= tr[u][id].r){
        return tr[u][id].v;
    }
    int mid = tr[u][id].l + tr[u][id].r >> 1;
    int tmpMax = LLONG_MIN;
    if(id == 1) tmpMax *= -1;
    if(l <= mid){
    	if(id == 0){
    		tmpMax = max(tmpMax, askVal(lc, l, r, id));
    	}
    	else{
    		tmpMax = min(tmpMax, askVal(lc, l, r, id));
    	}
    	
    }
    if(r > mid) {
    	if(id == 0){
    		tmpMax = max(tmpMax, askVal(rc, l, r, id));
    	}
    	else{
    		tmpMax = min(tmpMax, askVal(rc, l, r, id));
    	}
    }
    return tmpMax;
}

map<int, int> cnt; // 维护数字出现次数
set<pair<int, int> > st; // cnt[x] = 1 {pos, x}
vector<int> pos[N];



void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		pos[i].clear();
    }
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
    build(1, 1, n, 0);
    build(1, 1, n, 1);
    int wpc = 1;
    vector<int> res;
    for(int i = 1; i <= n; i ++){
    	int p = -1;
    	if(st.size()) p = (*st.begin()).first;
    	else p = n;

    	if(wpc)cout << i << ' ' <<p << '\n';

    	// i 到 p 里面选择一个数
    	if(i & 1){ // 此时选择最大值
    		// seg 查找一个没被考虑过的最大值
    		int mx = askVal(1, i, p, 0);
    		if(wpc)cout << mx << '\n';
    		int maxPos = lower_bound(pos[mx].begin(), pos[mx].end(), mx) - pos[mx].begin();
    		if(wpc) cout << maxPos<<'\n';
    		for(auto &p : pos[mx]){
    			change(1, p, -2e9, 0);
    		}
    		res.push_back(mx);
    		for(int j = i; j <= maxPos; j ++){
    			cnt[a[j]] --;
    			if(cnt[a[j]] == 1){
    				st.insert({j, a[j]});
    			}
    		}
    		i = maxPos;
    	}
    	else{
    		int mn = askVal(1, i, p, 0);
    		int minPos = lower_bound(pos[mn].begin(), pos[mn].end(), mn) - pos[mn].begin();
    		for(auto &p : pos[mn]) {
    			change(1, p, 2e9, 1);
    		}
    		res.push_back(mn);
    		for(int j = i; j <= minPos; j ++){
    			cnt[a[j]] --;
    			if(cnt[a[j]] == 1){
    				st.insert({j, a[j]});
    			}
    		}
    		i = minPos;
    	}
    }
    for(auto &p : res){
    	cout << p << ' ';
    }
    cout << '\n';
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}