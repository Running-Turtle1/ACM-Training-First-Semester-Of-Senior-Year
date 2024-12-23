#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int N = 4E5 + 10;
int prim[N], st[N], cnt = 0;
int dmin[N];

void solve(){
    int n;
    cin >> n;
    vector<int> a(n + 1);
    set<int> st_;
    for(int i = 1; i <= n; i ++) {
        cin >> a[i];
        // cout << a[i] << ' ' << dmin[a[i]] << '\n';
        if(!st[a[i]]) {
            st_.insert(a[i]);
        }
    }
    if(st_.size() > 1) {
        cout << "-1\n";
        return ;
    }

    if(st_.size() == 0) {
        cout << "2\n";
        return ;
    }

    auto x = *st_.begin();
    for(int i = 1; i <= n; i ++) {
        if(a[i] != x && a[i] != 2 * x && a[i] - dmin[a[i]] < 2 * x) {
            cout << "-1\n";
            return ;
        }
    }
    cout << x << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    st[1] = true;
    for(int i = 2; i < N; i ++) {
        if(!st[i]) {
            prim[cnt ++] = i;
        }
        for(int j = 0; i * prim[j] < N; j ++) {
            dmin[i * prim[j]] = prim[j]; // 每个数最小的约数
            st[i * prim[j]] = 1;
            if(i % prim[j] == 0) break;
        }
    } 

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}