#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 4e5 + 10;
int const sz = __lg(N) + 3;

int n, m;
int f[N][sz];

struct tp{
	int l, r, id;
	bool operator < (const tp & t){
		return l < t.l;
	}
};

void solve(){
	vector<tp > seg;
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		int l, r;
		cin >> l >> r;
		if(l < r){
			seg.push_back({l, r, i});
			seg.push_back({l + m, r + m, i});
		}
		else{
			seg.push_back({l, r + m, i});
			seg.push_back({l + m, 2 * m + 1, i});
		}
	}
	sort(seg.begin(), seg.end());
	// f[i][0] : 从线段 i 跳 1 步最远到的线段
	for(int i = 0; i < seg.size(); i ++){
		auto [lf, ri, id] = seg[i];
		if(ri == 2 * m + 1){
			f[i][0] = 2 * n + 1;
			continue ;
		}
		int l = 0, r = seg.size() - 1;
		while(l < r){
			int mid = l + r + 1 >> 1;
			if(seg[mid].l <= ri) l = mid;
			else r = mid - 1;
		}
		f[i][0] = l;
	}
	for(int j = 0; j < sz; j ++){
		f[2 * n + 1][j] = 2 * n + 1;
	}
	for(int j = 1; j < sz; j ++){
		for(int i = 0; i <= 2 * n; i ++){
			f[i][j] = f[f[i][j - 1]][j - 1];
		}
	}
	auto check = [&] (int id, int k) -> bool {
		int now = id;
		for(int j = 0; j < 20; j ++){
			if(k >> j & 1){
				now = f[now][j];
			}
		}
		return now == 2 * n + 1 || seg[now].r >= seg[id].l + m;
	};

	vector<int> ans(n + 1);

	for(int i = 0; i < n; i ++){
		int l = 1, r = n;
		while(l < r){
			int mid = l + r >> 1;
			if(check(i, mid)) r = mid;
			else l = mid + 1;
		}
		ans[seg[i].id] = l + 1;
	}
	for(int i = 1; i <= n; i ++){
		cout << ans[i] << " \n"[i == n];
    }
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