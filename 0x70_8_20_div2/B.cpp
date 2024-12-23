#include<bits/stdc++.h>
using namespace std;
#define int long long

// 打表找规律
// 找到了奇数的构造方法
// 以及偶数为什么不存在
void solve(){
	int n;
	cin >> n;
	std::vector<int> a(n);
	vector<int> st(n, 0);
	for(int i = 1; i <= n; i ++){
		a[i - 1] = i;
    }
    do{
    	fill(st.begin(), st.end(), 0);
    	int s1 = 0;
    	int now = 1;
    	while(true){
    		s1 ++;
    		for(int i = 0; i < n; i ++){
	    		if(st[i]) continue ;
	    		if(a[i] == now){
	    			now ++;
	    			st[i] = true;
	    		}
	    	}
	    	bool fg = true;
    		for(int i = 0; i < n; i ++){
    			if(!st[i]) fg = false;
    		}
    		// s1 ++;
    		if(fg) break;
    	}
    	
    	fill(st.begin(), st.end(), 0);
    	int s2 = 0;
    	now = 1;
    	while(true){
    		s2 ++;
    		for(int i = n - 1; i >= 0; i --){
	    		if(st[i]) continue ;
	    		if(a[i] == now){
	    			now ++;
	    			st[i] = true;
	    		}
	    	}
	    	bool fg = true;
    		for(int j = 0; j < n; j ++){
    			if(!st[j]) fg = false;
    		}
    		if(fg) break;
    	}
    	
    	// cout << s1 << ' ' << s2 << '\n';
    	if(s1 == s2  ){
    		for(int i = 1; i <= n; i ++){
    			cout << a[i - 1] << " \n"[i == n];
    		}
    	}
    }
    while(next_permutation(a.begin(), a.end()));
}

void solve_(){
	int n;
	cin >> n;
	if(n & 1){
		// (n - 1) / 2
		for(int i = 1; i <= (n - 1) / 2; i ++){
			cout << i << ' ';
		}
		cout << n << ' ';
		for(int i = n - 1; i > (n - 1) / 2; i --){
			cout << i << ' ';
		}
		cout << '\n';
	}
	else{
		cout << "-1\n";
	}
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve_();
	}

	return 0;
}