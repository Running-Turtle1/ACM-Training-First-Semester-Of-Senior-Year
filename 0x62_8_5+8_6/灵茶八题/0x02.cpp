#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int a[200010];

int sol1(int n, int *a){ // 所有子段和的和
	int res = 0;
	for(int i = 1; i <= n; i ++){
		res += i * (n - i + 1) * a[i];
    }
    return res;
}

int sol2(int n, int *a){ // 所有子段异或和的异或和
	int res = 0;
	for(int i = 1; i <= n; i ++){
		int t = i * (n - i + 1);
		if(t & 1) res ^= a[i];
    }
    return res;
}

int sol3(int n, int *a){ // 所有子段异或和的和
	int const sz = __lg(*max_element(a + 1, a + n + 1)) + 3;
	vector<vector<int> > sum(n + 1, vector<int> (sz + 1, 0)); // 1 的个数前缀和 (第 j 位 )

	int res = 0;
	for(int i = 1; i <= n; i ++){
		a[i] ^= a[i - 1];
		for(int j = 0; j < sz; j ++){
    		sum[i][j] = sum[i - 1][j] + (a[i] >> j & 1);
    	}
    }
    for(int i = 1; i <= n; i ++){
    	for(int j = 0; j < sz; j ++){
    		int num1 = sum[i - 1][j];
    		if(a[i] >> j & 1){ // 当前位是 1
    			int num0 = i - num1; // 注意 s[0] = 0
    			res += (1LL << j) * num0;
    		}
    		else{ // 当前位是 0
    			res += (1LL << j) * num1;
    		}
    	}
    }
    return res;
}

int sol4(int n, int *a){ // 所有子段和的异或和
	// 预处理前缀和
	for(int i = 1; i <= n; i ++){
		a[i] += a[i - 1];
    }

	// 树状数组 : 所有下标 + 1 离散化
	vector<int> tr(a[n] + 1, 0);
	auto add = [&] (int idx, int val){
		for(int i = idx + 1; i <= a[n]; i += i & -i){
			tr[i] += val;
		}
	};
	auto ask = [&] (int l, int r) {
		int res = 0;
		for(int i = r + 1; i > 0; i -= i & -i) res += tr[i];
		for(int i = l; i > 0; i -= i & -i) res -= tr[i];
		return res;
	};

    int res = 0;
    for(int k = 0; (1LL << k) <= a[n]; k ++){ // 考虑第 k 位的贡献
    	add(0, 1); // a[0] = 1

    	int cnt = 0;
    	for(int i = 1; i <= n; i ++){
    		int ts = a[i] & ((1LL << (k + 1)) - 1); // s % 2^(k+1)
    		if(a[i] >= 1LL << (k + 1)) ts |= 1 << (k + 1); // 借位的条件

    		int r = ts - (1LL << k), l = ts - ((1LL << (k + 1)) - 1);
    		cnt += ask(l, r);
    		r -= (1LL << (k + 1)), l -= (1LL << (k + 1));
    		cnt += ask(l, r);

    		add(a[i] & ((1LL << (k + 1)) - 1), 1);
    	}	

    	if(cnt & 1) res |= (1LL << k);

    	fill(tr.begin(), tr.end(), 0);
    }	
    return res;
}

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i]; 
    }
    cout << sol4(n, a) << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
