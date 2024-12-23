#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, k;

void solve(){
    cin >> n >> m >> k;
    vector<pair<int, int> > center;
    int tn = n, tm = m;
    int x1 = 1, x2 = n, y1 = 1, y2 = m;
    while(tn >= 3 && tm >= 3){
        tn -= 2;
        tm -= 2;
        x1 ++, x2 --;
        y1 ++, y2 --;
    }
    int res = 0;
    while(k --){
        int x, y;
        cin >> x >> y;
        if(x >= x1 && x <= 2)
        int fall = min({x, n - x + 1, y, m - y + 1});
        int dis = 2e9;
        for(int i = x1; i <= x2; i ++){
            dis = min(dis, abs(x - i));
        }
        for(int i = y1; i <= y2; i ++){
            dis = min(dis, abs(y - i));
        }
        if(dis < fall) res ++;
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}