#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	// for(int i = 1; i <= 10; i ++){
    //     for(int j = 1; j <= 10; j ++){
    //         if(i + j == 9 && 5*i+7*j>=50&&5*i+7*j<55){
    //         	cout<<i<<' '<<j<<'\n';
    //         	break;
    //         }
    //     }
    // }
    int k, x, y;
    cin>> k >> x >> y;
    if(x > y) swap(x, y); // x 小
    int mn = (k + y - 1) / y;
    int mx = (k + x - 1) / x;
    if((mn & 1) ^ (mx & 1)){
    	cout << "Yes\nYes\n";
    }
    else if(mn == mx){
    	cout << ((mx & 1) ? "YES\nNO\n" : "NO\nYES\n");
    }
    else{
    	cout << "YES\nYES\n";
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin>>t;
	while(t--) 
	solve();
	return 0;
}
