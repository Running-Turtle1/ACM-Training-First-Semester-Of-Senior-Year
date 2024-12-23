#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lc u << 1
#define rc u << 1 | 1

int const N = 2e5 + 10;

struct treeNode{
    int l, r, sum, change_tag;
}tr[N * 4];

void pushup(int u){
    tr[u].sum = tr[lc].sum + tr[rc].sum;
}

void pushdown(int u){
    if(tr[u].change_tag != -1){
        tr[lc].sum = (tr[lc].r - tr[lc].l + 1) * tr[u].change_tag;
        tr[rc].sum = (tr[rc].r - tr[rc].l + 1) * tr[u].change_tag;
        tr[lc].change_tag = tr[u].change_tag;
        tr[rc].change_tag = tr[u].change_tag;
        tr[u].change_tag = -1;
    }
}

void buildTree(int u, int l, int r){
    tr[u] = {l, r, 0, -1};
    if(l == r) return ;
    int mid = l + r >> 1;
    buildTree(lc, l, mid);
    buildTree(rc, mid + 1, r);
    pushup(u);
}

// 将 [l, r] 所有的数修改为 v
void SegmentChange(int u, int l, int r, int v){
    if(l <= tr[u].l && r >= tr[u].r){
        tr[u].sum = (tr[u].r - tr[u].l + 1) * v;
        tr[u].change_tag = v;
        return ;
    }
    // 分裂线段
    int mid = tr[u].l + tr[u].r >> 1;
    // 下传懒标记
    pushdown(u);
    if(l <= mid) SegmentChange(lc, l, r, v);
    if(r > mid) SegmentChange(rc, l, r, v);
    pushup(u);
}

// 区间求和
int AskSegmentSum(int u, int l, int r){
    if(l <= tr[u].l && r >= tr[u].r){
        return tr[u].sum;
    }
    // 分裂线段
    int mid = tr[u].l + tr[u].r >> 1;
    // 下传懒标记
    pushdown(u);
    int sum = 0;
    if(l <= mid) sum += AskSegmentSum(lc, l, r);
    if(r > mid) sum += AskSegmentSum(lc, l, r);
    return sum;
}

int n, a[N], b[N];
int preA[N], sufA[N], preB[N], sufB[N];

int askAgcd(int l, int r){
	int d = 0;
	for(int i = l; i <= r; i ++) d = __gcd(d, a[i]);
	return d;
}

int askBgcd(int l, int r){
	int d = 0;
	for(int i = l; i <= r; i ++) d = __gcd(d, b[i]);
	return d;
}
// map<int, std::vector<pair<int,int>> v;> mp[N];
int sche[N];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		// mp[i].clear();
    }
    for(int i = 1; i <= n; i ++){
    	cin >> b[i];
    }
    a[n + 1] = b[n + 1] = 0;
    sufA[n + 1] = sufB[n + 1] = 0;
    for(int i = 1; i <= n; i ++){
    	sche[i] = 0;
    	preA[i] = __gcd(preA[i - 1], a[i]);
    	preB[i] = __gcd(preB[i - 1], b[i]);
    }
    for(int i = n; i >= 1; i --){
    	sufA[i] = __gcd(sufA[i + 1], a[i]);
    	sufB[i] = __gcd(sufB[i + 1], b[i]);
    }

    int ans = 0;
    
    buildTree(1, 1, n);
    for(int i = 1; i <= n; i ++){
    	// i : 左端点
    	// [j, n] 未处理过的右端点
    	// [l, r1] 的变化点, 对 A 来说
    	SegmentChange(1, 1, n, 0);
    	set<pair<int, int> > pos;
    	int j = i;
    	while(j <= n){
    		int Jgcd = askAgcd(i, j);
    		int l = j, r = n;
    		while(l < r){
    			int mid = l + r + 1 >> 1;
    			if(askAgcd(i, mid) == Jgcd) l = mid;
    			else r = mid - 1;
    		}
    		pos.insert({j, l});
    		j = l + 1;
    	}
    	// [l, r1] 的变化点, 对 B 来说
    	j = i;
    	while(j <= n){
    		int Jgcd = askBgcd(i, j);
    		int l = j, r = n;
    		while(l < r){
    			int mid = l + r + 1 >> 1;
    			if(askBgcd(i, mid) == Jgcd) l = mid;
    			else r = mid - 1;
    		}
    		pos.insert({j, l});
    		j = l + 1;
    	}

    	j = n;
    	while(j >= i){
    		int Jgcd = sufA[j];
    		int l = i, r = j;
    		while(l < r){
    			int mid = l + r >> 1;
    			if(sufA[mid] == Jgcd) r = mid;
    			else l = mid + 1;
    		}
    		pos.insert({l, j});
    		j = l - 1;
    	}

    	j = n;
    	while(j >= i){
    		int Jgcd = sufB[j];
    		int l = i, r = j;
    		while(l < r){
    			int mid = l + r >> 1;
    			if(sufB[mid] == Jgcd) r = mid;
    			else l = mid + 1;
    		}
    		pos.insert({l, j});
    		j = l - 1;
    	}

    	for(auto [l, r] : pos){
    		// cout << "SegFOr: " << i << '\n';
    		// cout << l << ' ' << r << '\n';
    		int t1 = __gcd(preA[i - 1], askBgcd(i, l));
    		t1 = __gcd(t1, sufA[l + 1]);
    		int t2 = __gcd(preB[i - 1], askAgcd(i, l));
    		t2 = __gcd(t2, sufB[l + 1]);
    		ans = max(ans, t1 + t2);
    		// mp[i].push_back{l, r};
    		// SegmentChange(1, l, r, 1);

    		// mp[t1 + t2] += r - l + 1;
    	}
    	// cout << "Ans: ";
    	// cout << i << ' ' << AskSegmentSum(1, 1, n) << '\n';
    	// cout << mp[0] << '\n';
    	// mp[0] += AskSegmentSum(1, 1, n);
    } 
    int res =0;
    for(int i = 1; i <= n; i ++){
    	// i : 左端点
    	// [j, n] 未处理过的右端点
    	// [l, r1] 的变化点, 对 A 来说
    	SegmentChange(1, 1, n, 0);
    	set<pair<int, int> > pos;
    	int j = i;
    	while(j <= n){
    		int Jgcd = askAgcd(i, j);
    		int l = j, r = n;
    		while(l < r){
    			int mid = l + r + 1 >> 1;
    			if(askAgcd(i, mid) == Jgcd) l = mid;
    			else r = mid - 1;
    		}
    		pos.insert({j, l});
    		j = l + 1;
    	}
    	// [l, r1] 的变化点, 对 B 来说
    	j = i;
    	while(j <= n){
    		int Jgcd = askBgcd(i, j);
    		int l = j, r = n;
    		while(l < r){
    			int mid = l + r + 1 >> 1;
    			if(askBgcd(i, mid) == Jgcd) l = mid;
    			else r = mid - 1;
    		}
    		pos.insert({j, l});
    		j = l + 1;
    	}

    	j = n;
    	while(j >= i){
    		int Jgcd = sufA[j];
    		int l = i, r = j;
    		while(l < r){
    			int mid = l + r >> 1;
    			if(sufA[mid] == Jgcd) r = mid;
    			else l = mid + 1;
    		}
    		pos.insert({l, j});
    		j = l - 1;
    	}

    	j = n;
    	while(j >= i){
    		int Jgcd = sufB[j];
    		int l = i, r = j;
    		while(l < r){
    			int mid = l + r >> 1;
    			if(sufB[mid] == Jgcd) r = mid;
    			else l = mid + 1;
    		}
    		pos.insert({l, j});
    		j = l - 1;
    	}

    	for(auto [l, r] : pos){
    		cout << "SegFOr: " << i << '\n';
    		cout << l << ' ' << r << '\n';
    		int t1 = __gcd(preA[i - 1], askBgcd(i, l));
    		t1 = __gcd(t1, sufA[l + 1]);
    		int t2 = __gcd(preB[i - 1], askAgcd(i, l));
    		t2 = __gcd(t2, sufB[l + 1]);
    		if(t1+t2==ans) SegmentChange(1,l,r,1);
    		// ans = max(ans, t1 + t2);
    		// mp[i].push_back{l, r};
    		// SegmentChange(1, l, r, 1);

    		// mp[t1 + t2] += r - l + 1;
    	}
    	cout << "L: " << i<< '\n';
    	cout << AskSegmentSum(1, 1, n) << '\n';
    	res+=AskSegmentSum(1,1,n);
    	// cout << "Ans: ";
    	// cout << i << ' ' << AskSegmentSum(1, 1, n) << '\n';
    	// cout << mp[0] << '\n';
    	// mp[0] += AskSegmentSum(1, 1, n);
    } 
 	// int res_= 0;
 	// for(int i = 1; i <= n; i ++){
 	// 	SegmentChange(1,1,n,0);
 	// 	for(auto& [l, r] : mp[i]){
 	// 		SegmentChange(1,l,r,1);
 	// 	}
 	// 	res_+=AskSegmentSum(1,1,n);
    // }

    cout<<ans<<' '<<res<<'\n';
 	// cout << ans << ' ' << mp[0] << '\n';
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