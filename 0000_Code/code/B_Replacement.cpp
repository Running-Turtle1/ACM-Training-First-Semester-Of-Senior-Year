#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
string s, r;

void solve(){
    cin >> n >> s >> r;
    int cnt[2] = {0, 0};
    int del[2] = {0, 0};
    for(auto &nx : s) cnt[nx - '0'] ++;
    for(int i = 0; i + 1 < n; i ++) {
        int t = (r[i] - '0') ^ 1;
        del[t] ++;
        if(cnt[t] >= del[t] && del[t ^ 1] < cnt[t ^ 1]) {

        }
        else {
            cout << "NO\n";
            return ;
        }
    }
    cout << "YES\n";
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