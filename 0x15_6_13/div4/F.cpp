#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 200010;

int h, n;
// int damage[N]; // damage[i] 表示冷却为 i 的伤害
int a[N], c[N];

bool check(int x){
	int s = 0;
	for(int i = 1; i <= n; i ++){
		int t = (x - 1) / c[i] + 1;
		s = s + t * a[i];
		if(s >= h) return true;
    }
    return false;
}

void solve(){
	cin >> h >> n;
	// int firstTurns = 0;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		// firstTurns += a[i];
		// damage[c[i]] += a[i];
    }
    for(int i = 1; i <= n; i ++){
    	cin >> c[i];
    }
    int l = 1, r = 4e11;
    while(l < r){
    	int mid = l + r >> 1;
    	if(check(mid)) r = mid;
    	else l = mid + 1;
    }
    cout << l << '\n';
    // if(firstTurns >= h){
    // 	cout << "1\n";
    // }
    // else{
    // 	h -= firstTurns;
    // 	for(int i = 2; )
    // }

	// // 清空 vector
}



signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	int T;
	cin >> T;
	while(T --){
		solve();	
	}
	
	return 0;
}