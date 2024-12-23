# [Codeforces Round 970 (Div. 3)](https://codeforces.com/contest/2008)

## A

本质就是把 $a$ 个 $1$ 和 $b$ 个 $2$ 分为两个总和相等的数组。

那么就要求 $a+2b$ 是偶数。

其实 $a$ 与 $b$ 是偶数显然对半分。

$b$ 是奇数的话，$a=0$ 一定无解 ；$a\neq 0$ 时，$a$ 一定是偶数，把 $2$ 个 $1$ 分出来，$1$ 个 $2$ 分到另一个数组即可，剩下的重新对半分。

```cpp
// 问题等价于将 a 个 1 和 b 个 2 分成两个和相等的数组
// 要求总和是偶数

void solve(){
    int a, b;
    cin >> a >> b;
    if((a + 2 * b) & 1){
        cout << "NO\n";
        return ;
    }
    if(a % 2 == 0 && b % 2 == 0){
        cout << "YES\n";
    }
    else if(b % 2 == 1){ // 奇数个 2
        if(a == 0){ // 一定不合法
            cout << "NO\n";
        }
        else{ // 一边分两个 1, 另一边分 1 个 2
            cout << "YES\n";
        }
    }
}
```

或者直接暴搜，枚举一下符号即可。

```cpp
int n, a, b;
int tp[22], st[22];
bool fg = false;

void dfs(int u){
    if(u == n + 1){
        int res = 0;
        for(int i = 1; i <= n; i ++){
            int t = tp[i] == 0 ? 1 : -1;
            res += t * (i <= a ? 1 : 2);
        }
        if(!res) fg = true;
        return ;
    }

    tp[u] = 0;
    dfs(u + 1);

    tp[u] = 1;
    dfs(u + 1);
}

void solve(){
    cin >> a >> b;
    n = a + b; 
    fg = false;
    dfs(1);
    cout << (fg ? "YES" : "NO") << '\n';
}
```

再或者直接二进制枚举。

```cpp
void solve(){
    int a, b;
    cin >> a >> b;

    bool fg = false;
    int n = a + b;
    for(int i = 0; i < (1 << n); i ++){
        int res = 0;
        for(int j = 0; j < n; j ++){
            int t = (j < a ? 1 : 2);
            if(i >> j & 1){ // +
                res += t;
            }
            else{ // -
                res -= t;
            }
        }
        if(res == 0) fg = true;
    }

    cout << (fg ? "YES" : "NO") << '\n';
}
```

## B

首先 $n$ 必须是完全平方数，是的话可以选择暴力填一下矩阵，或者直接判断都行。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
string s;

bool check(int a, int b){
    vector<vector<int> > matrix(a + 1, vector<int> (b + 1, 0));
    for(int i = 1; i <= a; i ++){
        for(int j = 1; j <= b; j ++){
            matrix[i][j] = s[(i - 1) * a + j] - '0';
        }
    }
    for(int i = 1; i <= b; i ++){
        if(matrix[1][i] != 1 || matrix[a][i] != 1) return false;
    }
    for(int i = 1; i <= a; i ++){
        if(matrix[i][1] != 1 || matrix[i][b] != 1) return false;
    }
    for(int i = 2; i < a; i ++){
        for(int j = 2; j < b; j ++){
            if(matrix[i][j] != 0) return false;
        }
    }
    return true;
}

void solve(){
    cin >> n >> s;
    s = ' ' + s;

    int x = sqrt(n);
    if(n % x != 0){
        cout << "No\n";
        return ;
    }
    if(x != n / x){
        cout << "No\n";
        return ;
    }
    int y = n / x;
        if(check(x, y)){
            cout << "Yes\n";
            return ;
        }
    // }
    cout << "No\n";
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
```

## C

显然贪心来填。

```cpp
void solve(){
    int l, r;
    cin >> l >> r;
    int cnt = 1, t = 1;
    while(true){
        l += t ++;
        if(l > r) break;
        cnt ++;
    }
    cout << cnt << '\n';
}
```

## D

很常见的 Trick ，见注释

```cpp
// 这种给出一个排列的题目, 且如果存在 i -> p_i
// 或者 p_i -> i 的边
// 那么一定会构成若干环
// 知道这个性质, 用任意方法维护一个环里面有多少个黑色的点即可

int const N = 2e5 + 10;

int n, x, p[N], to[N], st[N], f[N], c[N];

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        st[i] = 0;
        cin >> x;
        to[i] = x;
    }

    string str;
    cin >> str;
    for(int i = 0; i < str.size(); i ++){
        c[i + 1] = (str[i] == '0' ? 0 : 1);
    }

    for(int i = 1; i <= n; i ++){
        // cout << "i: " << i << '\n';
        if(!st[i]){
            stack<int> stk;

            int sz = 0;

            int at = i;
            while(true){
                stk.push(at);
                st[at] = 1;
                if(c[at] == 0) sz ++;
                at = to[at];
                if(at == i) break;
            }

            // int sz = stk.size();
            while(stk.size()){
                x = stk.top();
                stk.pop();
                f[x] = sz;
            }
        }
    }

    for(int i = 1; i <= n; i ++){
        cout << f[i] << " \n"[i == n];
    }
}
```

## E

可以用 $dp$ ，下面是 $dp$ 代码

```cpp
// 这里采用了 DP 的解法
// dp[i][0 / 1] 表示考虑到第 i 个字符，
// 是否使用第二种操作, 使得[1,i] 是交替字符的方案数

int const inf = 2e18;

int n;
string s;
vector<array<int, 2> > f(200010);

void deal(int i, int j){
    for(int i = 1; i <= n; i ++){
        f[i][0] = f[i][1] = 2e18;
    }    
    char fs = ('a' + i), sc = ('a' + j); // fs sc
    f[1][0] = (s[1] == fs ? 0 : 1);
    f[1][1] = 1;
    for(int i = 2; i <= n; i ++){
        char t = (i & 1) ? fs : sc;
        char ano = (i & 1) == 0 ? fs : sc;
        f[i][0] = min(f[i][0], f[i - 1][0] + (s[i] != t));
        f[i][1] = min({f[i][1], f[i - 1][0] + 1, f[i - 1][1] + (s[i] != ano)});
    }
}

void solve(){
    cin >> n >> s;
    s = ' ' + s;

    int res = 2e18;
    for(int i = 0; i < 26; i ++){
        for(int j = 0; j < 26; j ++){
            deal(i, j);
            if(n & 1) res = min(res, f[n][1]);
            else res = min(res, f[n][0]);
        }
    }
    cout << res << '\n';
}
```

也可以不用，因为偶数一定不删，奇数一定删一次。

那么偶数的把奇偶位置变成出现最多的即可。

奇数的话，枚举删除位置 $i$ , 注意 $(i,n]$ 位置要调换奇偶性。

```cpp
int const N = 2e5 + 10;

int n;
string str;

int oddcnt[N][26], evencnt[N][26];

void solve(){
    cin >> n >> str;
    str = ' ' + str;
    for(int i = 1; i <= n; i ++){
        for(int j = 0; j < 26; j ++){
            oddcnt[i][j] = oddcnt[i - 1][j];
            evencnt[i][j] = evencnt[i - 1][j];
        }
        if(i & 1) oddcnt[i][str[i] - 'a'] ++;
        else evencnt[i][str[i] - 'a'] ++;
    }
    auto askodd = [&] (int l, int r, int id) -> int {
        if(l > r) return 0;
        return oddcnt[r][id] - oddcnt[l - 1][id];
    };
    auto askeven = [&] (int l, int r, int id) -> int {
        if(l > r) return 0;
        return evencnt[r][id] - evencnt[l - 1][id];
    };
    if(n & 1){ // 使用一次删除操作
        int res = 2e18;
        for(int i = 1; i <= n; i ++){
            int mxodd = -2e18, mxeven = -2e18;
            for(int j = 0; j < 26; j ++){
                mxodd = max(mxodd, askodd(1, i - 1, j) + askeven(i + 1, n, j));
                mxeven = max(mxeven, askeven(1, i - 1, j) + askodd(i + 1, n, j));
            }
            res = min(res, n - mxodd - mxeven);
        }
        cout << res << '\n';
    }
    else{ // 不使用删除操作
        cout << n - *max_element(oddcnt[n], oddcnt[n] + 26) - *max_element(evencnt[n], evencnt[n] + 26) << '\n';
    }
}
```

## F

很基础的一个期望。

```cpp
void solve(){
    sum = 0;
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        sum = (sum + a[i]) % mod;
    }

    int res = 0;
    for(int i = 1; i <= n; i ++){
        int t = (sum - a[i]) % mod;
        if(t < 0) t += mod;
        res = (res + a[i] * t % mod) % mod;
    }
    // cout << res << '\n';
    cout << res * inv(n * (n - 1) % mod) % mod << '\n';
}
```

## G

对于 $x$ 和 $y$ ，发现题目的操作类似更相减损术的过程，一定得到的 $\gcd(x,y)$ ，再来一个 $z$ ，再做更相减损，能得到 $\gcd(x,y,z)$ 

设 $g=\gcd _{i=1}^na_i$ 

最终能得到 $g$ ，所有数会变为 $g$ 的倍数。

我们贪心的构造出 $0,g,2g,3g,\cdots,(n-1)g$ 。

然后模拟一下去填 $k-1$ 个数。

可以加个 trick, 添加 $a_{n+1}=+\infty$ ，方便 code。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, k, g, a[N];

void solve(){
	g = 0;
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		g = __gcd(g, a[i]);
    }
    if(n != 1){
    	for(int i = 1; i <= n; i ++){
    		a[i] = g * (i - 1);
    	}
    }

    a[++ n] = 1e18; // 方便处理数组的 trick
    k --; // 允许补 k - 1 次没出现的数
    int now; // [0, now] 都出现了
    if(a[1] == 0) now = 0;
    else{ // a[1] != 0
    	if(k == 0){
    		cout << "0\n";
    		return ;
    	}
    	k --;
    	now = 0;
    }

    for(int i = 1; i <= n; i ++){
    	if(now == a[i] || now == a[i] - 1){
    		now = a[i];
    	}
    	else{
    		// [now + 1, a[i] - 1]
    		int t = (a[i] - 1) - (now + 1) + 1;
    		if(k >= t){
    			k -= t; // 补上
    			now = a[i];
    		}
    		else{
    			cout << now + k + 1 << '\n';
    			return ;
    		}
    	}
    }
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
```

## H

用到两个 trick，找第 $k$ 小的数，二分所有数，右边区间的 $x$ 满足 $\leq x$ 的数 $\geq k$ 个，二分最大最小。

第二个 trick 就是，[1, n] 对 $x$ 取模是循环的，所以对于不同的 $x$ ，$\sum \frac n  x$ 的复杂度是调和的，记忆化之后枚举段即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, q, a[N], cnt[N];

void solve(){
	cin >> n >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		cnt[i] = 0;
	}
	for(int i = 1; i <= n; i ++){
		cnt[a[i]] ++;
    }
    for(int i = 1; i <= n; i ++){
    	cnt[i] += cnt[i - 1];
    }
    vector<int> f(n + 1, -1);
    int x;
    int lim = ((n & 1) ? ((n + 1) / 2) : (n + 2) / 2); // 中位数位置
    // cout << lim << '\n';
    function<bool(int)> check = [&] (int mid) -> bool {
    	int res = 0;
    	for(int i = 0; i <= n; i += x){
    		// [i, i + mid]
    		int r = i + mid > n ? n : i + mid;
    		res += (i ? cnt[r] - cnt[i - 1] : cnt[r]);
    	}
    	return res >= lim;
    };

    for(int i = 1; i <= q; i ++){
    	cin >> x;
    	if(f[x] != -1){
    		cout << f[x] << ' ';
    		continue ;
    	}
    	int l = 0, r = x - 1;
    	while(l < r){
    		int mid = l + r >> 1;
    		if(check(mid)) r = mid;
    		else l = mid + 1;
    	}
    	f[x] = l;
    	cout << f[x] << ' ';
    }
    cout << '\n';
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
```
