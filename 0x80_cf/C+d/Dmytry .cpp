#include<bits/stdc++.h>
using namespace std;
#define int long long

int read(){
	int res = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		res = res * 10 + (ch - '0');
		ch = getchar();
	}
	return res;
}

int const N = 2e5 + 10;
int const M = __lg(N) + 3;

int n, a[N], b[N];
int sta[N][M], stb[N][M];
int Log2[N];
int preA[N], preB[N];
int sufA[N], sufB[N];
int ask(int l, int r, int id){
	if(l > r) return 0;
	int s = Log2[r - l + 1];
	if(id == 0)return __gcd(sta[l][s], sta[r - (1 << s) + 1][s]);
	return __gcd(stb[l][s], stb[r - (1 << s) + 1][s]);
}
void solve(){
	n = read();
	for(int i = 1; i <= n; i ++){
		a[i] = read();
    }
    for(int i = 1; i <= n; i ++){
    	b[i] = read();
    }
    for(int i = 1; i <= n; i ++){
    	sta[i][0] = a[i], stb[i][0] = b[i];
    	preA[i] = __gcd(preA[i - 1], a[i]);
    	preB[i] = __gcd(preB[i - 1], b[i]);
    }
    a[n + 1] = sufA[n + 1] = 0;
    b[n + 1] = sufB[n + 1] = 0;
    for(int i = n; i >= 1; i --){
    	sufA[i] = __gcd(sufA[i + 1], a[i]);
    	sufB[i] = __gcd(sufB[i + 1], b[i]);
    }
    for(int j = 1; j < M; j ++)
    	for(int i = 1; i + (1 << j) - 1 <= n; i ++){
    		sta[i][j] = __gcd(sta[i][j - 1], sta[i + (1 << (j - 1))][j - 1]);
    		stb[i][j] = __gcd(stb[i][j - 1], stb[i + (1 << (j - 1))][j - 1]);
    	}
    
    int ans = 0, cnt = 0;
    // 做 GCD 每次会减少一半, 枚举左端点的话
    // 最多 4\log 个位置, \log 二分找到所有点
    for(int i = 1; i <= n; i ++){
    	int j = i; // 当前位置
    	while(j <= n){
    		int l = j, r = n;
    		while(l < r){
    			int mid = l + r + 1 >> 1;
    			if(ask(j, mid, 0) == a[j] && ask(j, mid, 1) == b[j] && sufA[mid + 1] == sufA[j + 1] && sufB[mid + 1] == sufB[j + 1]){
    				l = mid;
    			}
    			else{
    				r = mid - 1;
    			}
    		}

    		// [j, l] 作为右端点
    		int t1 = __gcd(preA[i - 1], __gcd(ask(i, j, 1), sufA[j + 1]));
    		int t2 = __gcd(preB[i - 1], __gcd(ask(i, j, 0), sufB[j + 1]));
    		if(t1 + t2 > ans){ 
    			ans = t1 + t2;
    			cnt = l - j + 1;
    		}
    		else if(t1 + t2 == ans){
    			cnt += l - j + 1;
    		}
    		j = l + 1;
    	}
    }
    printf("%lld %lld\n", ans, cnt);;
    // cout << ans << ' ' << cnt << '\n';
}	

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0); 

	for(int i = 2; i < N; i ++) Log2[i] = Log2[i / 2] + 1;

	int T;
	T = read();
	while(T --){
		solve();
	}

	return 0;
}
