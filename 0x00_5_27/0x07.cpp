#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	string s;
	int k, n;
	cin >> s >> k;
	n = s.size();
	int cnt[62];
	fill(cnt, cnt + 62, 0);
	// for(int i = 1; i <= 61; i ++){
	// 	cout << cnt[i] << '\n';
    // }
    auto get = [] (char x){
    	if(x >= 'a' && x <= 'z') return x - 'a'; // [0, 25]
    	if(x >= 'A' && x <= 'Z') return x - 'A' + 26; 
    	return x - '0' + 52;
    };
    for(auto &x : s) cnt[get(x)] ++;
    // for(int i = 0; i <= 61; i ++){
    // 	cout << cnt[i] << " \n"[i == 61];
    // }
    int res = n;
    for(int l = 0; l <= n - k; l ++){
    	int r = l + k;
    	// [l, r]
    	int tmp = 0;
    	for(int j = 0; j < 62; j ++){
    		if(cnt[j] == 0) continue;
    		if(cnt[j] >= l && cnt[j] <= r) continue;
    		if(cnt[j] < l) tmp += cnt[j];
    		if(cnt[j] > r) tmp += -r + cnt[j];
    	}
    	res = min(res, tmp);
    }
    cout << res << '\n';
    // int res = n;
    // for(int i = 0; i < 62; i ++){
    // 	bool fg = true;
    // 	int tmp = 0;
    // 	for(int j = 0; j < 62; j ++){
    // 		if(j == i) continue;
    // 		if(cnt[j] >= cnt[i] - k && cnt[j] <= cnt[i] + k){
    // 			continue;
    // 		}
    // 		if(cnt[j] < cnt[i] - k){
    // 			tmp += cnt[j];
    // 		}
    // 		else{
    // 			tmp += min(cnt[j], cnt[j] - (cnt[i] + k));
    // 		}
    		
    // 	}
    // 	if(fg) res = min(res, tmp);
    // }
    // cout << res << '\n';
}
// 枚举字符串出现次数范围, [i, i+k], 因为数据太少直接算
// 1 2 3 5
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}