#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 100010;

int n, a[N], root;
int sz[N]; // 以 u 为根的子树中支撑结点的数量
int weight[N]; // 以 u 为根的子树的权值和
int fg[N]; // u 是不是支撑点

vector<int> e[N];

int dfs1(int u){ // 记忆化搜索 weight
	if(weight[u] != 0) return weight[u];
	weight[u] = a[u];
	for(auto &v : e[u]){
		dfs1(v);
		weight[u] += weight[v];
	}
	return weight[u];
}

void dfs2(int u, int sumP){
	if(a[u] <= sumP && a[u] >= weight[u] - a[u]){
		sz[u] = 1;
		fg[u] = 1;
	}
	for(auto &v : e[u]){
		dfs2(v, sumP + a[u]);
		sz[u] += sz[v];
	}
}

int const M = N * 2;
int tr[M];
void add(int p, int v){
	for(int i = p; i < M; i += i & -i){
		tr[i] += v;
	}
}
int ask(int p){
	int res = 0;
	for(int i = p; i; i -= i & -i){
		res += tr[i];
	}
	return res;
}
int ask(int l, int r){
	return ask(r) - ask(l - 1);
}

int weightMiuns[N];

int res; // 初始答案
// 计算答案
void dfs(int u, int sumP){
	// cout << "dfs: " << u << '\n';
	int tmp = res - sz[u] + ask(1, weight[u] - 1);
	res = max(res, tmp);

	// cout << u << ' ' <<ask(1, weight[u]) << '\n';

	// if(u == 4){
	// 	cout << tmp << '\n';
	// }

	// 加到树状数组
	if(a[u] <= sumP && fg[u] == 0){
		add(weightMiuns[u], 1);
	}

	for(auto &v : e[u]){
		dfs(v, sumP + a[u]);
	}

	if(a[u] <= sumP && fg[u] == 0){
		add(weightMiuns[u], -1);
	}
}



int btmp[N << 1]; // 离散化所有 weight 和 差

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    for(int i = 1; i <= n; i ++){
    	int p;
    	cin >> p;
    	e[p].push_back(i);
    }
    dfs1(1);
    dfs2(1, 0); // 处理 sz
    // cout << "weight: \n";
    // for(int i = 1; i <= n; i ++){
    // 	cout << weight[i] << " \n"[i == n];
    // }
    // cout << "sz: \n";
    // for(int i = 1; i <= n; i ++){
    // 	cout << sz[i] << " \n"[i == n];
    // }
    for(int i = 1; i <= n; i ++){
    	weightMiuns[i] = weight[i] - 2 *  a[i];
    	btmp[i] = weightMiuns[i];
    }
    // cout << "weightMiuns: \n";
    // for(int i = 1; i <= n; i ++){
    // 	cout << weightMiuns[i] << " \n"[i == n];
    // }
    for(int i = 1; i <= n; i ++){
    	btmp[n + i] = weight[i];
    }
    sort(btmp + 1, btmp + 2 * n + 1);
    int siz = unique(btmp + 1, btmp + 2 * n + 1) - btmp - 1;
    for(int i = 1; i <= n; i ++){
    	weight[i] = lower_bound(btmp + 1, btmp + siz + 1, weight[i]) - btmp;
    }
    for(int i = 1; i <= n; i ++){
    	weightMiuns[i] = lower_bound(btmp + 1, btmp + siz + 1, weightMiuns[i]) - btmp;
    }
	res = sz[1]; // 初始化答案
	dfs(1, 0);
	cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
