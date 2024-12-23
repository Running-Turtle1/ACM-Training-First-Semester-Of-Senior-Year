#include<bits/stdc++.h>
using namespace std;
#define int long long
int in[10010];
void solve(){
	int a, b, cnt = 1;
	while(cin >> a >> b){
		if(a == -1 && b == -1) return ;
		if(a == 0 && b == 0){
			int s0 = 0, s1 = 0, s2 = 0;
			for(int i = 1; i <= 10000; i ++){
				if(in[i] == 0) s0 ++;
				else if(in[i] == 1) s1 ++;
				else s2 ++;
			}
			cout << s0 << ' ' << s1 << ' ' << s2 << '\n';
			if(s2 || s0 != 1){
				cout << "Case " << cnt << " is a tree.\n";
			}
			else{
				cout << "Case " << cnt << " is not a tree.\n";
			}
			for(int i = 1; i <= 10000; i ++) in[i] = 0;
			cnt ++;
			continue ;
		}
		in[b] ++;
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
// 只有一个 in[] = 0, else = 1