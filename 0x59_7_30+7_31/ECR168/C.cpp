#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n;
string str;

int cnt = 0;
int l[N];

void solve(){
	cin >> n >> str;
	str = ' ' + str;

	int sum = 0;
	int res = 0;

	for(int i = 1; i <= n; i ++){
		if(i & 1){
			if(sum == 0){
				sum ++;
				l[++ cnt] = i;
			}
			else{
				sum --;
				res += i - l[cnt --];
			}
		}
		else{
			if(str[i] == '('){
				sum ++;
				l[++ cnt] = i;
			} 
			else{
				sum --;
				res += i - l[cnt --];
			}
		}
	}

	cout << res << '\n';
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