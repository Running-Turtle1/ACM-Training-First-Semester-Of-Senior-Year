#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n;
    cin >> n;
    vector<string> s(n + 1);
    for(int i = 1; i <= n; i ++){
        cin >> s[i];
    }
    for(int i = 1; i <= n; i ++){
        if(i + 1 <= n - 1 && s[i] == "sweet" && s[i + 1] == "sweet"){
            cout << "No\n";
            return ;
        }
    }
    cout << "Yes\n";
}
// 除非最后遇到 sweet + sweet, 否则只要遇到就是 No
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
