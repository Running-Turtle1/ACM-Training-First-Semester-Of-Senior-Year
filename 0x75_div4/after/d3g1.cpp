#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, k, q;
int a[N], ans[N];

void solve(){
	map<int, int> cnt;
	multiset<int> st;
	cin >> n >> k >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		cnt[i] = 0;
    }
    for(int i = 1; i <= n; i ++){
    	a[i] -= (i - 1);
    }
    st.insert(0); //
    auto add = [&] (int x) -> void {
    	if(cnt[x]) st.erase(st.find(cnt[x]));
    	cnt[x] ++;
    	st.insert(cnt[x]);
    };
    auto del = [&] (int x) -> void {
    	st.erase(st.find(cnt[x]));
    	cnt[x] --;
    	st.insert(cnt[x]);
    };
    int mx = 0;
    for(int i = 1; i <= k; i ++){
    	add(a[i]);
    }
    ans[1] = k - (*st.rbegin());
    for(int i = k + 1; i <= n; i ++){
    	int l = i - k + 1;
    	del(a[l - 1]);
    	add(a[i]);
    	ans[l] = k - (*st.rbegin());
    }
    while(q --){
    	int l, r;
    	cin >> l >> r;
    	cout << ans[l] << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T;
	cin >> T;
	while(T --){
		solve();
	}

	return 0;
}