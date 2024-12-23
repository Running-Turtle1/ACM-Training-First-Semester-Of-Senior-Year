## A

分情况讨论

```cpp
void solve(){
    char c1, c2, c3;
    cin >> c1 >> c2 >> c3;
    if(c1 == c3){
        cout << "B";
    }
    else{
        if(c1 == '<'){
            if(c2 == '<') cout << "C";
            else cout << "A";
        }
        else{
            if(c2 != '<') cout << "C";
            else cout << "A";
        }
    }
}
```

三对关系，如果 $a<b$ ，就从 $a$ 向 $b$ 连边，统计哪个点入度为 $1$ ，他就是 $middle$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    char sab, sac, sbc;
    cin >> sab >> sac >> sbc;
    std::vector<int> in(3);
    if(sab == '<') in[1] ++;
    else in[0] ++;
    if(sbc == '<') in[2] ++;
    else in[1] ++;
    if(sac == '<') in[2] ++;
    else in[0] ++;
    for(int i = 0; i < 3; i ++){
        if(in[i] == 1){
            cout << (char)('A' + i);
            break;
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```

## B

模拟

```cpp
int n, k;
int st[110];

void solve(){
    cin >> n >> k;
    for(int i = 1; i <= k; i ++){
        int a;
        char b;
        cin >> a >> b;
        if(b == 'F'){
            cout << "No\n";
        }
        else{
            if(st[a]) cout << "No\n";
            else{
                cout << "Yes\n";
                st[a] = 1;
            }
        }
    }
}
```

## C

> 给定两个图 $G$ 和 $H$ 。
> 
> 要求对 $H$ 操作，使得 $H$ 与 $G$ 同构，花费的最小代价。

一开始想的是枚举 $H$ 排列，把他变得与 $G$ 相同，这样显然是不对的，过不了样例。

实际就是操作 $G$ ，让 $G$ 变的与 $H$ 的其中一个排列相同，因此枚举所有 $H$ 的排列即可，$O(n!(m_G+m_H))$ 

```cpp
int n, m1, m2;
int g1[10][10], g2[10][10];
int t[10][10], a[10][10], p[10];

void solve(){ 
    cin >> n;
    cin >> m1;
    for(int i = 1; i <= m1; i ++){
        int a, b; 
        cin >> a >> b;
        g1[a][b] = g1[b][a] = 1;
    }
    cin >> m2;
    for(int i = 1; i <= m2; i ++){
        int a, b;
        cin >> a >> b;
        g2[a][b] = g2[b][a] = 1;
    }
    for(int i = 1; i <= n; i ++){
        for(int j = i + 1; j <= n; j ++){
            cin >> a[i][j];
        }
    }
    iota(p + 1, p + n + 1, 1);
    int ans = 1e9;
    do{
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= n; j ++){
                t[i][j] = 0;
            }
        }
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= n; j ++){
                if(g1[i][j]){
                    t[p[i]][p[j]] = 1;
                }
            }
        }
        int res = 0;
        for(int i = 1; i <= n; i ++){
            for(int j = i + 1; j <= n; j ++){
                if(g2[i][j] && !t[i][j]){ // 多余边
                    res += a[i][j];
                }
                if(!g2[i][j] && t[i][j]){ // 缺失边
                    res += a[i][j];
                }
            }
        }
        ans = min(ans, res);
    }
    while(next_permutation(p + 1, p + n + 1));
    cout << ans << '\n';
}
```

## D

> 下标范围比较大，询问区间和。

离散化维护前缀和即可。

实际上二分也可以做。

```cpp
int const N = 1e6 + 10;
int cnt = 0, t[N], x[N], p[N], l[N], r[N], s[N];
int n, q;

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> x[i];
        t[++ cnt] = x[i];
    }
    for(int i = 1; i <= n; i ++){
        cin >> p[i];
        // t[++ cnt] = p[i];
    }
    cin >> q;
    for(int i = 1; i <= q; i ++){
        cin >> l[i] >> r[i];
        t[++ cnt] = l[i];
        t[++ cnt] = r[i];
    }
    sort(t + 1, t + cnt + 1);
    int sz = unique(t + 1, t + cnt + 1) - t - 1;
    for(int i = 1; i <= n; i ++){
        x[i] = lower_bound(t + 1, t + sz + 1, x[i]) - t;
    }
    for(int i = 1; i <= q; i ++){
        l[i] = lower_bound(t + 1, t + sz + 1, l[i]) - t;
        r[i] = lower_bound(t + 1, t + sz + 1, r[i]) - t;
        // cout << x[i] << ' ' << l[i] << ' ' << r[i] << '\n';
    }
    for(int i = 1; i <= n; i ++){
        s[x[i]] += p[i];
    }
    for(int i = 1; i <= cnt; i ++){
        s[i] += s[i - 1];
    }
    for(int i = 1; i <= q; i ++){
        cout << s[r[i]] - s[l[i] - 1] << '\n';
    }
}
```

## E

发现，倒着来考虑，当前考虑到 $x$ 的话，设 $p$ 是 $x$ 上一次出现的位置。

那么以 $x$ 当前位置 $i$ 开头的子数组中，$[i,p)$ 的变化是上次的 $+1$ ，$[p,n]$ 则不变。

因此用线段树维护这些区间操作。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, a[N];

#define lc u << 1
#define rc u << 1 | 1

// 维护端点, 线段和, 加法懒标记
struct treeNode{
    int l, r, sum, add;
}tr[N * 4];

// 向上更新
void pushup(int u){
    tr[u].sum = tr[lc].sum + tr[rc].sum;
}

// 向下更新
void pushdown(int u){
    if(tr[u].add){
        tr[lc].sum += tr[u].add * (tr[lc].r - tr[lc].l + 1);
        tr[rc].sum += tr[u].add * (tr[rc].r - tr[rc].l + 1);
        tr[lc].add += tr[u].add;
        tr[rc].add += tr[u].add;
        tr[u].add = 0;
    }
}

void buildTree(int u, int l, int r){
    tr[u] = {l, r, 0, 0};
    if(l == r) return ; // 是叶子结点则返回
    int mid = l + r >> 1; // 不是叶子结点就分裂
    buildTree(lc, l, mid);
    buildTree(rc, mid + 1, r);
    pushup(u);
}

// 区间加 (区间减也是区间加)
void segmentAdd(int u, int l, int r, int x){
    if(l <= tr[u].l && r >= tr[u].r){ // 覆盖则修改
        tr[u].sum += (tr[u].r - tr[u].l + 1) * x;
        tr[u].add += x;
        return ;
    }
    int mid = tr[u].l + tr[u].r >> 1; // 不覆盖就分裂
    pushdown(u);
    if(l <= mid) segmentAdd(lc, l, r, x);
    if(r > mid) segmentAdd(rc, l, r, x);
    pushup(u);
} 

// 区间求和
int askSegmentSum(int u, int l, int r){
    if(l <= tr[u].l && r  >= tr[u].r){ // 覆盖则返回
        return tr[u].sum;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    int sum = 0;
    if(l <= mid) sum += askSegmentSum(lc, l, r);
    if(r > mid) sum += askSegmentSum(rc, l, r);
    return sum;
}

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }        
    buildTree(1, 1, n);
    map<int, int> pos;
    int ans = 0;
    for(int i = n; i >= 1; i --){
        int p = n + 1;
        if(pos.count(a[i])) p = pos[a[i]];
        segmentAdd(1, i, p - 1, 1);
        pos[a[i]] = i;
        ans += askSegmentSum(1, i, n);
        // cout << "change: " << i << ' ' << p - 1 << '\n';
        // for(int i = 1; i <= n; i ++)
        //     cout << askSegmentSum(1, i, i) << " \n"[i == n];
        // cout << i << ' ' << askSegmentSum(1, i, n) << '\n';
    }
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```

下面提供一种简洁的解法 ：

发现数字的值域有限，（其实很大的值域也可以离散化）

考虑每个数字 $x$ 会出现在多少不同的子区间中，设出现了 $cnt_x$ 次。

答案就是 $\sum cnt_x$ 。

假设 $x$ 在 $a $ 中只出现 $1$ 次，且出现在位置 $p$ ，那么子区间共有 $p\times (n-p+1)$ 种。

其中，$p$ 是左端点可以选的数量，$n-p+1$ 是右端点可以选的数量。

假设 $x$ 在 $a$ 出现了很多次，以出现三次为例，假设出现在 $p_1,p_2,p_3$ 这三个位置。

那么枚举左端点，在 $p_1$ 之前的，右端点可以选 $[p_1,n]$ 。

在 $(p_1,p_2]$ 的，可以选 $[p2,n]$ 。

以此类推。

每个位置，可以带来的贡献就是，$(p_i-p_{i-1})\times (n-p_i+1)$ 。

```cpp
int const N = 2e5 + 10;
int n, a[N], las[N];

void solve(){
    int res = 0;
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        res += (i - las[a[i]]) * (n - i + 1);
        las[a[i]] = i;
    }
    cout << res << '\n';
}
```

## F

题目类似于推积木的过程。

我们二分寻找每次移动多少人受影响，然后把这一段区间修改为等差数列。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;
int const inf = 9e18;

#define lc u << 1
#define rc u << 1 | 1

// 线段树维护两个信息
// s1 表示首项和
// s2 维护公差和, 每个位置 i = i * d
// 所以区间修改的时候, 以 [3, 5] 修改为 1 2 3 为例
// 我们维护的第二项公差是 3 4 5
// 每个位置多维护了 3, 所以首项都要减掉 3, 一般化就是减去 L * d
struct Node{
	int l, r;
	int s1, s2, lz1, lz2;
}tr[N << 2];

void work(int u, int lz1, int lz2){
	if(lz1 != inf){
		tr[u].s1 = (tr[u].r - tr[u].l + 1) * lz1;
		tr[u].lz1 = lz1;
	}
	if(lz2 != inf){
		tr[u].s2 = (tr[u].r - tr[u].l + 1) * (tr[u].l + tr[u].r) / 2 * lz2;
		tr[u].lz2 = lz2;
	}
}

void pushup(int u){
	tr[u].s1 = tr[lc].s1 + tr[rc].s1;
	tr[u].s2 = tr[lc].s2 + tr[rc].s2;
}

void pushdown(int u){
	work(lc, tr[u].lz1, tr[u].lz2);
	work(rc, tr[u].lz1, tr[u].lz2);
	tr[u].lz1 = tr[u].lz2 = inf;
}

// 建一颗空树
void build(int u, int l, int r){
	tr[u] = {l, r, 0, 0, inf, inf};
	if(l == r) return ;
	int mid = l + r >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
	pushup(u);
}

// 把 [l, r] 范围修改为首项为 d1, 公差为 d2 的等差数列
// 主要传参 : modify(1, l, r, d1 - l * d2, d2)
void modify(int u, int l, int r, int d1, int d2){
	if(l <= tr[u].l && r >= tr[u].r){
		work(u, d1, d2);
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) modify(lc, l, r, d1, d2);
	if(r > mid) modify(rc, l, r, d1, d2);
	pushup(u);
}

int ask(int u, int l, int r){
	if(l <= tr[u].l && r >= tr[u].r){
		return tr[u].s1 + tr[u].s2;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	int res = 0;
	if(l <= mid) res += ask(lc, l, r);
	if(r > mid) res += ask(rc, l, r);
	return res;
}

void solve(){
	int n;
	cin >> n;
	build(1, 1, n);
	vector<int> x(n + 1);
	for(int i = 1; i <= n; i ++){
		cin >> x[i];
		modify(1, i, i, x[i], 0);
	} 
	int q, ans = 0;
	cin >> q;
	while(q --){
		int t, g;
		cin >> t >> g;
		int xt = ask(1, t, t);
		if(g > xt) {
			int l = t, r = n;
			while(l < r){
				int mid = l + r + 1 >> 1;
				if(ask(1, mid, mid) < g + mid - t) l = mid;
				else r = mid - 1;
			}	
			ans += (l - t + 1) * (2 * g + l - t) / 2 - ask(1, t, l);
			modify(1, t, l, g - t * 1, 1);
			 
		}
		else if(g < xt){
			int l = 1, r = t;
			while(l < r){
				int mid = l + r >> 1;
				if(ask(1, mid, mid) > g - (t - mid)) r = mid;
				else l = mid + 1; 
			}
			ans += ask(1, l, t) - (t - l + 1) * (2 * g + l - t) / 2 ;
			modify(1, l, t, g - t, 1);
		} 
	}
	cout << ans << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}

```
