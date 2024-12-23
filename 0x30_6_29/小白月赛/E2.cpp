#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, q, b[N];
int neg[N]; // 负数绝对值前缀和
int s[N][110]; // 正数 j 的数量前缀和

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> b[i];
        neg[i] = neg[i - 1] + (b[i] < 0 ? -b[i] : 0);
        for(int j = 1; j <= 100; j ++){
            s[i][j] = s[i - 1][j] + (b[i] == j);
        }
    }
    auto ask = [&] (int l, int r){
        int has = neg[r] - neg[l - 1];
        int sum = 0;
        for(int i = 1; i <= 100; i ++){
            int tmp = s[r][i] - s[l - 1][i];
            if(has >= tmp * i){
                has -= tmp * i;
                sum += tmp;
            }
            else{
                return sum + has / i;
            }
        }  
        return sum;
    };
    cin >> q;
    while(q --){
        int l, r;
        cin >> l >> r;
        cout << ask(l, r) + 1 << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
