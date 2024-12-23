#include<bits/stdc++.h>
using namespace std;
// #define int long long

int const N = 2e5 + 10;

int n, q;
int a[N];

struct node{
	int p, k, id;
	bool operator < (const node & T){
		return k < T.k;
	}
}info[N];

int ans[N];

int result[N];
void simulate(int k){
	int level = 1;
	int s = 0;
	for(int i = 1; i <= n; i ++){
		if(level > a[i]){
			result[i] = 0;
		}
		else{
			result[i] = 1;
			s ++;
			if(s >= k) s -= k, level ++;
		}
	}
}

int sum[N][505];

void solve(){
	cin >> n >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    for(int i = 1; i <= q; i ++){
    	int p, k;
    	cin >> p >> k;
    	info[i] = {p, k, i};
    }
    sort(info + 1, info + q + 1);

    int lim = sqrt(n * log2(n));
    if(lim == 0) lim = 1;
    // int lim = sqrt(n);
    // vector<vector<int> > sum(n + 1, vector<int> (lim + 1, 0)); // sum[i][level] 预处理位置 [1 ~ i] 对 level 贡献的前缀和
    for(int i = 1; i <= n; i ++){
    	for(int j = 1; j <= lim; j ++){
    		sum[i][j] = sum[i - 1][j] + (a[i] >= j);
    	}
    }
    auto ask = [&] (int l, int r, int level) -> int {
    	if(l > r) return 0;
    	return sum[r][level] - sum[l - 1][level];
    };

    // cout << "result: \n";
    // simulate(1);
    // for(int i = 1; i <= 4; i ++){
    // 	cout << i << ' ' << result[i] << '\n';
    // }
    // return ;

    int las = 0;
    for(int i = 1; i <= q; i ++){
    	auto &[p, k, id] = info[i];
    	if(k <= lim){
    		if(k != las){
				simulate(k);
				las = k;
			}
			ans[id] = result[p];
    	}
    	else{
    		p --; // 看看到 p-1 的时候能到多少级

    		int level = 1;
    		int nowPos = 0;

    		while(true){
    			if(ask(nowPos + 1, n, level) < k) break; // 不能再升级
    			int l = nowPos + 1, r = n;
    			while(l < r){
    				int mid = l + r >> 1;
    				if(ask(nowPos + 1, mid, level) >= k) r = mid;
    				else l = mid + 1;
    			}
    			if(l > p) break;
    			level ++;
    			nowPos = l;
    		}

    		ans[id] = level <= a[p + 1];
    	}
    }

    for(int i = 1; i <= q; i ++){
    	if(ans[i] == 2e9){
    		cout << "No consider\n";
    		continue ;
    	}
    	cout << (ans[i] ? "YES" : "NO") << "\n";
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
