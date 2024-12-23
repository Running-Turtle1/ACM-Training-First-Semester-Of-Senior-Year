#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n;
	cin >> n;

	vector<int> a(n + 1), mx(n + 1, 0);
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		mx[i] = i == 1 ? a[i] : max(a[i], mx[i - 1]);
    }
    for(int i = 1; i <= n; i ++){
    	if(mx[i] - mx[i - 1] > 1){
    		cout << "-1\n";
    		return ;
    	}
    }
    vector<int> res(n + 1);
    vector<vector<int> > pos(n + 1);
    for(int i = 1; i <= n; i ++){
    	pos[a[i]].push_back(i);
    }
    for(int i = 1; i <= n; i ++){
    	sort(pos[i].begin(), pos[i].end(), [&] (int a, int b){
    		return a > b;
    	});
    };
    int now = 1;
    for(int i = 1; i <= n; i ++){
    	for(auto &p : pos[i]) res[p] = now ++;
    }
	for(int i = 1; i <= n; i ++){
		cout << res[i] << ' ';
    }


}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
