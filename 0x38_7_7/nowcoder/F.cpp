#include<bits/stdc++.h>
using namespace std;
#define int long long
bool isSq(int x){
    return (int)(sqrt(x))*((int)(sqrt(x)))==x;
}
void solve(){
    int r;
    cin >> r;
    int sqrtr = sqrt(r);
    
    int gcd=0;
    bool fg=false;
    for(int i = 0; i <= sqrtr; i ++){
        int j = r - i * i;
        if(isSq(j)){ // (i, j)
            fg=true;
            gcd=__gcd(gcd, j);
            gcd=__gcd(gcd, i);
        }
    }
    if(fg){
        cout<<gcd*gcd<<'\n';
    }
    else{
        cout<<"inf\n";
    }
//     if((int)sqrt(r) * (int)sqrt(r) != r){ // 非完全平方数
//         cout << "inf\n";
//     }
//     else if(r == 1){
//         cout << "1\n";
//     }
//     else{
//         for(int i = 0; i <= sqrt(r) + 10; i ++){
//             int j = r - i * i;
//         } 
//     }
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