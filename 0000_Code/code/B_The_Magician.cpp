#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n, s[4] = {0, 0, 0, 0};
    cin >> n;
    for(int i = 1; i <= n; i ++){
        string t;
        cin >> t;
        if(t.back() == 'D') s[3] ++;
        else if(t.back() == 'C') s[2] ++;
        else if(t.back() == 'H') s[1] ++;
        else s[0] ++;
    }
    int res = 0;
    for(int i = 0; i < 4; i ++){
        res += s[i] / 5;
        s[i] %= 5;
    }
    int c[6] = {0, 0, 0, 0, 0, 0};
    for(int i = 3; i >= 0; i --){
        cin >> c[i];
    }
    cin >> c[4] >> c[5];
    int mx = 0;
    for(int i = 0; i < ((1 << 4) - 1); i ++){
        int tmp = 0, r = 0, love = c[4] + c[5];
        bool fg = true;
        for(int j = 0; j < 4; j ++){
            if(!(i >> j & 1)){
                r += s[j];
            }
        }
        for(int j = 0; j < 4; j ++){
            if(i >> j & 1){
                int ned = 5 - s[j];
                if(ned <= 2) {
                    if((!c[j] && love < ned) || r < ned){
                        fg = false;
                        break;
                    }
                    if(!c[j]) {
                        love -= ned;
                    }
                    r -= ned, tmp ++;
                }
                else if(ned >= 3){
                    if(!c[j] || love < ned - 3 || r < ned){
                        fg = false;
                        break;
                    }
                    r -= ned;
                    ned -= 3;
                    love -= ned;
                    tmp ++;
                }
            }
        }
        if(fg) mx = max(mx, tmp);
    }
    cout << res + mx << '\n';
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