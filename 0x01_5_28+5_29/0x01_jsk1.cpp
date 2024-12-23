// 对于选定格子 (i, j) 为中心, 可以敲击的 row 为 :
// [i - k + 1, i + k - 1]


// 以 (5, 5), k = 3 为例 :
// 3 : [5 ~ 5] 
// 4 : [4 ~ 6] : 5 - k + 2, 5 + k - 2
// 5 : [3 ~ 7] : 5 - k + 1, 5 + k - 1
// 6 : [4 ~ 6]
// 7 : [5 ~ 7]
    
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
int a[2100][2100];
int s[2100][2100]; // s[i] 表示第 i 行的前缀和

void solve(){
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++){
			int x;
			cin >> x;
			a[i][j]=x;
			s[i][j] = s[i][j - 1] + x;
		}
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	for(int j = 1; j <= n; j ++){
    		// 需要计算的行
    		int tmp = 0;
    		for(int a = i - k + 1; a <= i + k - 1; a ++){
    			int t = k - abs(a - i) - 1;
    			int l = max(1LL, j - t);
    			int r = min(n, j + t);
    			tmp += s[a][r] - s[a][l - 1];
    			// if(i==2&&j==2){
    			// 	cout<<"MID: ";
    			// 	cout<<a<<' '<<l<<' '<<r<<'\n';
    			// }
    		}
    		tmp-=a[i][j];
    		res = max(res, tmp);
    		// cout<<i<<' '<<j<<' '<<tmp<<'\n';
    	}
    }
    cout << res << '\n';
}

signed main(){
    // freopen("challenge.in", "r", stdin);
    // freopen("challenge.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}