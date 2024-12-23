#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n, k;
	cin >> n >> k;
	vector<int> v;
	int ans = 1;
	int sum = 0;
	for(int i = 2; i <= n / i; i ++){
		int s = 0;
		while(n % i == 0) n /= i, s ++;
		if(s) s --, ans ++;
		if(s) v.push_back(s);
		sum += s;
	}
	if(n > 1) ans ++;
	if(!v.size()){
		cout << (ans >= k ? "TAK" : "NIE") << '\n';
		return ;
	}
	sort(v.begin(), v.end());
	if(v.back() > sum / 2){
		int t = v.back();
		ans += sum - t;
		t -= sum - t;
		for(int i = 2; ; i ++){
			if(t < i) break;
			t -= i;
			ans ++;
		}
	}
	else{
		ans += sum / 2;
	}
	cout << (ans >= k ? "TAK" : "NIE") << '\n';
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