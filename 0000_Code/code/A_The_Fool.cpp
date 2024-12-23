#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, k;

string s[210];

void solve(){
    map<string, int> mp;
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i ++){
        cin >> s[i];
        string t = "";
        for(int j = 1; j <= m * k; j ++){
            t += s[i][j - 1];
            if(j % k == 0){
                mp[t] ++;
                t = "";
            }
        }
    }
    // for(auto [x, y] : mp) cout << x << ' ' << y << '\n';
    for(int i = 1; i <= n; i ++){
        string t = "";
        for(int j = 1; j <= m * k; j ++){
            t += s[i][j - 1];
            if(j % k == 0){
                if(mp[t] == 1){
                    cout << i << ' ' << j / k << '\n';
                    break;
                }
                t = "";
            }
        }
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
