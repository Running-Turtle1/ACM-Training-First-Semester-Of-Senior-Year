## Problem Link

[Problem - F - Codeforces](https://codeforces.com/contest/1982/problem/F)

## Detailed Solution

[Codeforces Round 955 (Div. 2) A-F题解 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/705437500)

## Trick

- 用 set 维护可能不合法点的位置，快速锁定一个小区间

- 小区间两端的区间是有序的，二分找到需要 sort 的极限位置

- 需要用线段树维护区间最值，便于二分时使用

- 这道题关键就在于想到用 set 维护所有不有序的点，之后的一些操作就顺理成章的想出来了。

## Analysis

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
// #define int long long

template<typename T>
void read(T &x) {
    x = 0;
    int f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    x *= f;
}
template<typename T, typename... Args>
void read(T &x, Args&... args) {
    read(x);
    read(args...);
}
template<typename T>
void write_single(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write_single(x / 10);
    }
    putchar(x % 10 + '0');
}
template<typename T>
void write(T x) {
    write_single(x);
    putchar('\n');
}
template<typename T, typename... Args>
void write(T x, Args... args) {
    write_single(x);
    putchar(' ');
    write(args...);
}

int const N = 5e5 + 10;
int a[N]; 

#define lc u << 1
#define rc u << 1 | 1

struct TreeNode{
	int l, r;
	int mn, mx;
}tr[N * 4];

void pushup(int u){
	tr[u].mx = max(tr[lc].mx, tr[rc].mx);
	tr[u].mn = min(tr[lc].mn, tr[rc].mn);
}

void buildTree(int u, int l, int r){
	tr[u] = {l, r, a[l], a[l]};
	if(l == r) return ;
	int mid = l + r >> 1;
	buildTree(lc, l, mid);
	buildTree(rc, mid + 1, r);
	pushup(u);
}

int askSegmentMax(int u, int l, int r){
	if(l <= tr[u].l && r >= tr[u].r){
		return tr[u].mx;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	// int tmpMax = LLONG_MIN;
	int tmpMax = INT_MIN;
	if(l <= mid) tmpMax = max(tmpMax, askSegmentMax(lc, l, r));
	if(r > mid) tmpMax = max(tmpMax, askSegmentMax(rc, l, r));
	return tmpMax;
}

int askSegmentMin(int u, int l, int r){
	if(l <= tr[u].l && r >= tr[u].r){
		return tr[u].mn;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	// int tmpMin = LLONG_MAX;
	int tmpMin = INT_MAX;
	if(l <= mid) tmpMin = min(tmpMin, askSegmentMin(lc, l, r));
	if(r > mid) tmpMin = min(tmpMin, askSegmentMin(rc, l, r));
	return tmpMin;
}

void Modify(int u, int p, int v){
	if(tr[u].l == tr[u].r){
		tr[u] = {p, p, v, v};
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if(p <= mid) Modify(lc, p, v);
	else Modify(rc, p, v);
	pushup(u);
}

int n, q;


void solve(){
	set<int> s; // 表示不合法位置 i, 即 a[i] < a[i - 1]
	// s.clear();
	read(n);
	for(int i = 1; i <= n; i ++){
		read(a[i]);
		if(i != 1 && a[i] < a[i - 1]){
			s.insert(i);
		}
    }
    buildTree(1, 1, n);
    // cout << askSegmentMax(1, 1, n) << ' ' << askSegmentMin(1, 1, n) << '\n';
    read(q);
    for(int i = 0; i <= q; i ++){
    	int p, v;
    	if(i){
    		read(p, v);
    		// cin >> p >> v;
    		Modify(1, p, v);
    		a[p] = v;
    		if(p != 1 && a[p] < a[p - 1]){
    			// if(s.count(p) == false) 
    			s.insert(p);
    		}
    		else if(p != 1 && a[p] >= a[p - 1]){
    			// if(s.count(p)) 
    			s.erase(p);
    		}
    		if(p != n && a[p + 1] < a[p]){
    			//if(s.count(p + 1) == false) 
    			s.insert(p + 1);
    		}
    		else if(p != n && a[p + 1] >= a[p]){
    			// if(s.count(p + 1)) 
    			s.erase(p + 1);
    		}
    	}
    	// for(auto & p : s){
    	// 	cout << p << ' ';
    	// }
    	// cout << '\n';
    	if(s.size() == 0){
    		// cout << "-1 -1\n";
    		// write(-1, -1);
    		puts("-1 -1");
    	}
    	else{
    		int posL = *s.begin(), posR = *s.rbegin();
    		int MinOfSeg = askSegmentMin(1, posL, posR);
    		// if(posL == 1 || askSegmentMin(1, 1, posL - 1) > MinOfSeg){
    		// 	posL = 1;
    		// }
    		// else{
    		// if(posL != 1 && askSegmentMax(1, 1, posL - 1) > MinOfSeg){
    		if(posL != 1 && a[posL - 1] > MinOfSeg){
    			int l = 1, r = posL - 1;
    			while(l < r){
    				int mid = l + r >> 1;
    				if(a[mid] > MinOfSeg) r = mid;
    				else l = mid + 1;
    			}
    			posL = l;
    		}
    		// cout << posL << ' ' << posR << '\n';
    		int MaxOfSeg = askSegmentMax(1, posL, posR);
    		// cout << MaxOfSeg << '\n';
    		// cout << askSegmentMiif(posL != 1 && askSegmentMax(1, 1, posL - 1) > MinOfSeg){n(1, posR + 1, n)  << '\n';
    		if(posR != n && a[posR + 1] < MaxOfSeg){
    			int l = posR + 1, r = n;
    			while(l < r){
    				int mid = l + r + 1 >> 1;
    				if(a[mid] < MaxOfSeg) l = mid;
    				else r = mid - 1;
    			}
    			posR = l;
    		}
    		printf("%lld %lld\n", posL, posR);
    		// write(posL, posR);
    		// cout << posL << ' ' << posR << '\n';
    		// cout << posL << ' ' << posR << '\n';
    		// if(posR == n || as)
    	}
    }
}

signed main(){
	int T = 1;
	read(T);
	while (T --){
		solve();
	}

	return 0;
}
```
