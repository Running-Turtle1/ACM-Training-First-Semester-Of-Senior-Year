#include<bits/stdc++.h>
using namespace std;
#define int long long

int x;
int a[35];

void solve(){
    cin >> x;
    for(int i = 0; i < 32; i ++){
        a[i] = x >> i & 1;
    }
    // for(int i = 0; i < 32; i ++) cout << a[i] << ' ';
    // cout << '\n';
    for(int i = 0; i < 31; i ++){
        if(a[i] == 0) continue;
        else if(a[i] == 2){
            a[i] = 0;
            a[i + 1] ++;
        }
        else if(a[i] == -2){
            a[i] = 0;
            a[i + 1] --;
        }
        else if(a[i] == 1){
            if(a[i + 1] == 0) continue;
            else if(a[i + 1] == 1){
                a[i] = -1;
                a[i + 1] = 0;
                a[i + 2] ++;
            }
            else if(a[i + 1] == -1){
                a[i] = -1;
                a[i + 1] = 0;
            }
        }
        else if(a[i] == -1){
            if(a[i + 1] == 0) continue;
            else if(a[i + 1] == -1){
                a[i] = 1;
                a[i + 1] = 0;
                a[i + 2] --;
            }
            else if(a[i + 1] == 1){
                a[i] = 1;
                a[i + 1] = 0;
            }
        }
    }
    cout << 31 << '\n';
    for(int i = 0; i < 31; i ++) cout << a[i] << ' ';
    cout << '\n';
}
// 0 -1 1 1 1 0 0 0 0 0 0 0 0 0 0 
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