#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[10][10];
void solve(){
    for(int i = 1; i <= 3; i ++){
        for(int j = 1; j <= 3; j ++){
            a[i + j - 1][3 + j - i] = 1;
            cout<<i<<' '<<j<<" : " << i+j-1 << ' ' << 3+j-i << '\n';
        }
    }
    for(int i = 1; i <= 5; i ++){
        for(int j = 1; j <= 5; j ++){
            cout << a[i][j] <<" \n"[j == 5];
        }
    }

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}