#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n;
	string s;
	cin>>n>>s;
	bool fg1 = false, fg2 = false, fg = false;
	for(int i = 0; i < n; i ++){
		if(s[i] >= '0' && s[i] <= '9') fg1 = true;
		else if(s[i] >= 'a' && s[i] <= 'z') fg2 = true;
		else fg = true;
	}
	if(fg){
		cout << "NO\n";
		return ;
	}
	if(fg1 && fg2){
		int p;
		for(int i = 0; i < n; i ++){
			if(s[i] >= 'a' && s[i] <= 'z'){
				p = i;
				break;
			}
		}
		// [0,p-1]全是数字,[p,ed]全是字母
		// 而且必须升序
		for(int i=0;i<p;i++){
			if((s[i] >= '0' && s[i] <= '9')==false){
				cout << "NO\n";
				return ;
			}
		}
		for(int i=p;i<n;i++){
			if((s[i] >= 'a' && s[i] <= 'z')==false){
				cout << "NO\n";
				return ;
			}
		}
		for(int i=0;i+1<p;i++){
			if(s[i+1]<s[i]){
				cout << "NO\n";
				return ;
			}
		}
		for(int i=p;i+1<n;i++){
			if(s[i+1]<s[i]){
				cout << "NO\n";
				return ;
			}

		}
		cout<<"YES\n";
		return ;
	}
	if(fg1){
		for(int i = 0; i + 1 < n; i ++){
			if(s[i+1]<s[i]){
				cout << "NO\n";
				return ;
			}
		}
		cout<<"YES\n";
		return ;
	}
	for(int i = 0; i  + 1< n; i ++){
			if(s[i+1]<s[i]){
				cout << "NO\n";
				return ;
			}
		}
		cout<<"YES\n";
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