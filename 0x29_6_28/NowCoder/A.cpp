
#include<bits/stdc++.h>
using namespace std;

#define lc u << 1
#define rc u << 1 | 1

struct TreeNode{
    int l, r;
    int num;
    int Mul;
}tr[500];

void pushup(int u){
	tr[u].num = tr[lc].num + tr[rc].num;
	tr[u].Mul = tr[lc].Mul + tr[rc].Mul;
}

void buildTree(int u, int l, int r){
    tr[u] = {l, r, 0, 0};
    if(l == r) return ;
    int mid = l + r >> 1;
    buildTree(lc, l, mid);
    buildTree(rc, mid + 1, r);
    pushup(u);
}

int askSegmentNum(int u, int l, int r){
    if(l <= tr[u].l && r >= tr[u].r){
        return tr[u].num;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    int tmpRes = 0;
    if(l <= mid) tmpRes += tr[lc].num;
    if(r > mid) tmpRes += tr[rc].num;
    return tmpRes;
}

int askSegmentMul(int u, int l, int r){
    if(l <= tr[u].l && r >= tr[u].r){
        return tr[u].Mul;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    int tmpRes = 0;
    if(l <= mid) tmpRes += tr[lc].Mul;
    if(r > mid) tmpRes += tr[rc].Mul;
    return tmpRes;
}

void Modify(int u, int p, int v){
    if(tr[u].l == tr[u].r){
        tr[u] = {p, p, v, p * v};
        return ;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if(p <= mid) Modify(lc, p, v);
    else Modify(rc, p, v);
    pushup(u);
}

int const maxn = 1e5 + 10;

struct Q{
    int l, r, k;
}q[maxn];

int res;
int a[maxn], pos[maxn], ans[maxn];

int num[110]; // 值为 i 的正数的数量
int SumOfPositiveNum = 0; // 正数数量
int SumofNegative = 0; // 负数和的绝对值

int ask(){ 
	// int s = 0;
	// int res = 0;
	// for(int i = 1; i <= 100; i ++){
	// 	s += i * num[i];
	// 	res += num[i];
	// 	if(s > SumofNegative){
	// 		int tmp = SumofNegative - (s - i * num[i]);
	// 		return res - num[i] + tmp / i; // [1, i-1] 数量
	// 		break;
	// 	}
	// }
	// return SumOfPositiveNum; // 所有正数都失效
	if(SumofNegative > askSegmentMul(1, 1, 100)){
		return SumOfPositiveNum; // 所有正数都失效;
	}
	int l = 1, r = 100;
	while(l < r){
		int mid = l + r + 1 >> 1;
		if(askSegmentMul(1, 1, mid) <= SumofNegative) l = mid;
		else r = mid - 1;
	}
	return l;
}

void Add(int x){
	x = a[x];
	if(x > 0){ // 加正数
		// cout << x << '\n';
		SumOfPositiveNum ++;
		num[x] ++;
		Modify(1, x, num[x]);
	}
	else if(x < 0){ // 加负数
		SumofNegative += abs(x);
	}
	res = SumOfPositiveNum + 1;
	res = res - (SumOfPositiveNum - ask() + 1) + 1;
}

void Sub(int x){
	x = a[x];
	if(x > 0){ // 减正数
		SumOfPositiveNum --;
		num[x] --;
		Modify(1, x, num[x]);
	}
	else if(x < 0){ // 加负数
		SumofNegative -= abs(x);
	}
	res = SumOfPositiveNum + 1;
	res = res - (SumOfPositiveNum - ask() + 1) + 1;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
    // n m l r
    int n, m;
    cin >> n;
    // 分块
    int siz = sqrt(n);
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        pos[i] = i / siz;
    }
    cin >> m;
    for(int i = 0; i < m; i ++){
        cin >> q[i].l >> q[i].r;
        q[i].k = i;
    }
    sort(q, q + m, [](Q x, Q y){
        return pos[x.l] == pos[y.l] ? x.r < y.r : pos[x.l] < pos[y.l];
    });

    int l = 1, r = 0; // [l, r]
    for(int i = 0; i < m; i ++){
        while(q[i].l < l) Add(-- l);
        while(q[i].r > r) Add(++ r);
        while(q[i].l > l) Sub(l ++);
        while(q[i].r < r) Sub(r --);
        ans[q[i].k] = res;
    }
    // cout << SumOfPositiveNum << '\n';
    // cout << SumofNegative << '\n';
    cout << ask() << '\n';
    for(int i = 0; i < m; i ++)
        cout << ans[i] << '\n';

    return 0;
} 

// void solve(){

// }

// signed main(){
	
// 	solve();
// 	return 0;
// }
