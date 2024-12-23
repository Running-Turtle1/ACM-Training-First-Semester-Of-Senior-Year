#include<bits/stdc++.h>
using namespace std;
#define int long long

#define debug 1

int const N = 2e5 + 10;

int n, res = 0;
string s;
int pre[N];

vector<int> bk[N]; // 存放值为 i 的 pre[p] 的下标 p 

int const sz = __lg(N) + 2;
int f[N][sz]; // 计算区间 mx
int Log2[N];
struct ST{
	void init(int n){
		for(int i = 1; i <= n; i ++){
			f[i][0] = pre[i];
		}
		for(int i = 1; i < sz; i ++){
			for(int j = 1; j + (1 << i) - 1 <= n; j ++){
				f[j][i] = max(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);
			}
		}
	}

	int ask(int l, int r){
		int s = Log2[r - l + 1];
		return max(f[l][s], f[r - (1 << s) + 1][s]);
	}
}st;

// 二分第 idx 个 bk, 计算他能贡献多少答案
void sol(int idx){
	int n = bk[idx].size();
	for(int i = 0; i + 1 < n; i ++){
		int lpos = bk[idx][i]; // 左边的位置
		int x = pre[lpos];
		// 不存在满足条件的区间 
		if(st.ask(lpos + 1, bk[idx][i + 1]) > 2 * x){
			continue; 
		} 
		int l = i + 1, r = n - 1;
		while(l < r){
			int mid = l + r + 1 >> 1;
			if(st.ask(lpos + 1, bk[idx][mid]) <= 2 * x) l = mid;
			else r = mid - 1;
		}
		// if(i == 0)
		res += l - i;
	}
}

void solve(){
	cin >> s;
	n = s.size();
	s = ' ' + s;

	for(int i = 1; i <= n; i ++){
		pre[i] = pre[i - 1];
		if(s[i] == '(') pre[i] ++;
		else pre[i] --;
		bk[i].clear();
    }

    st.init(n);

    // debug 1
    // for(int i = 1; i <= n; i ++) cout << pre[i] << " \n"[i == n];
    // for(int i = 1; i <= n; i ++){
    //     for(int j = i; j <= n; j ++){
    //         cout << i << ' ' << j << ' ' << st.ask(i, j) << '\n';
    //     }
    // }

    // 1 这个位置不能被翻转, 直接特判掉
    // for(int i = 2; i <= n; i ++){
    // 	bk[pre[i]].push_back(i);
    // }
    for(int i = 1; i <= n; i ++){
    	bk[pre[i]].push_back(i);
    }

    // debug 2
    // for(int i = 0; i <= 1; i ++){
    // 	cout << "bk" << i << ": \n";
    // 	for(auto &p : bk[i]) cout << p << ' ';
    // 	cout << '\n';
    // }

    // if(debug){
    // 	sol(1);
    // 	return ;
    // }

    res = 0;
    for(int i = 1; i <= n; i ++){
    	if(bk[i].size() > 1){
    		sol(i);
    	}
    }

    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	for(int i = 2; i < N; i ++){
		Log2[i] = Log2[i / 2] + 1;
	}

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}