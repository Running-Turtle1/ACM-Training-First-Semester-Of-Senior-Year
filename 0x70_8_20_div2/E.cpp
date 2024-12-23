#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1

int const N = 3e5 + 10;

struct tree{
	int l, r;
	int v;
}tr[N][2];


int n, a[N];

void pushup(int u, int id){
	if(id == 0){
		tr[u][0].v = max(tr[lc][0].v, tr[rc][0].v);
	}
	else{
		tr[u][1].v = min(tr[lc][1].v, tr[rc][1].v);
	}
}

void build(int u, int l, int r, int id){
	tr[u][id] = {l, r, a[l]};
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

    build(1, 1, n, 0);
    build(1, 1, n, 1);

    cout << askVal(1, 1, n, 0) << '\n';
    cout << askVal(1, 1, n, 1) << '\n';



    return ;
 
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}