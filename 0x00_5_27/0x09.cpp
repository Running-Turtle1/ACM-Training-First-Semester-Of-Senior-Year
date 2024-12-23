// hint1 : 
// 每个元素要么来自于 a1, 要么来自于 a2, 都不来自方案为 0
    
// hint2 :
// 对于合法的方案, n 是偶数, a1 出 n/2 个数, a2 出 n/2 个数
// n 是奇数, a1 出 n/2 个数, a2 出 n/2 个数, 然后 a1 或者 a2 多出一个数

// hint3 :
// 题意 : 从 a1 里面选出前 n 个元素, a2 里面选出前 m 个元素, 构成 a3, 求有几种方案 ?
// f[i][j] 表示选 a1 前 i 个元素, a2 前 j 个元素, 构成 a3[i + j] 的总方案数
// 状态转移 : a[i + j] 由 a1 还是 a2 转移而来 ?
    
// if(a3[i + j] == a1[i]){
//     f[i][j] += f[i - 1][j];
// }
// if(a3[i + j] == a2[j]){
//     f[i][j] += f[i][j - 1];
// }

#include<bits/stdc++.h>
using namespace std;
#define int long long
int const mod = 1e9 + 7;
int n1, n2, n;
int f[8100][8100];
int a1[8100], a2[8100], a[8100];
void solve(){
    cin >> n1 >> n2 >> n;
    for(int i = 1; i <= n1; i ++){
        cin >> a1[i];
    }
    for(int i = 1; i <= n2; i ++){
        cin >> a2[i];
    }
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    int res = 0;
    f[0][0] = 1;
    for(int i = 0; i <= n1; i ++){
        for(int j = 0; j <= n2; j ++){
            if(!i && !j) continue;
            if(i + j > n) break;
            if(a[i + j] == a1[i]){
                f[i][j] = (f[i][j] + f[i - 1][j]) % mod;
            }
            if(a[i + j] == a2[j]){
                f[i][j] = (f[i][j] + f[i][j - 1]) % mod;
            }
            // if(i + j == n && abs(i - j) <= 1) res = max(res, f[i][j]);
        }
    }
    // cout << f[1][0] << '\n';
    // // cout << res;
    cout << f[n1][n2] << '\n';
    // if(n % 2 == 0) cout << f[n / 2][n / 2] << '\n';
}

signed main(){
    // // freopen("array.in", "r", stdin);
    // freopen("array.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
    
    