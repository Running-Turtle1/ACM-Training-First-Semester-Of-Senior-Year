#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 998244353;

int n, k;
string s;
int f[2][5100][4];

char op(char x){
    if(x == '0') return '1';
    if(x == '1') return '0';
    return ' ';
}

void solve(){
    cin >> n >> k >> s;
    s = ' ' + s;
    f[1][0][0] = 1; f[1][1][1] = 1;
    for(int i = 2; i <= n; i ++){
        int now = i & 1;
       memset(f[now], 0, sizeof f[now]);
        for(int j = 0; j <= k; j ++){
            for(int s1 = 0; s1 < 4; s1 ++){
                for(int s2 = 0; s2 < 4; s2 ++){
                    if((s1 >> 1 & 1) != (s2 & 1)) continue;
                    string str = "";
                    if(s2 >> 1 & 1) str += op(s[i - 2]);
                    else str += s[i - 2];
                    int t = 0;
                    if(s1 == 0) str += s[i - 1], str += s[i];
                    else if(s1 == 1) str += s[i - 1], str += op(s[i]), t = 1;
                    else if(s1 == 2) str += op(s[i - 1]), str += s[i];
                    else str += op(s[i - 1]), str += op(s[i]), t = 1;
                    if(str == "110") continue;
                    if(j >= t){
                        (f[now][j][s1] += f[now ^ 1][j - t][s2]) %= mod;
                    }
                }
            }
        }
    }
    int res = 0;
    for(int i = 0; i <= k; i ++){
        for(int j = 0; j < 4; j ++){
            (res += f[n & 1][i][j]) %= mod;
        }
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}