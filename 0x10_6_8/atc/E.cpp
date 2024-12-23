#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x = 0, f = 1; // f 代表正负 
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = x * 10LL + c - '0';
        c = getchar();
    }
    return x * f;
} 


int n;
int f[200010];
int to[200010];
// f[i] = \sigma f[j], 其中 j 是 i 的儿子结点
// 记忆化搜索一下 ?

int dfs(int u){
	if(f[u] != -1) return f[u];
	f[u] = 1;
	f[u] += dfs(f[to[u]]);
	return f[u];
}

void solve(){
	memset(f, -1, sizeof f);
	cin >> n;
	for(int i = 1; i <= n; i ++){
		to[i] = read();
    }
    dfs(1);
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	res += f[i];
    }
    cout << res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}