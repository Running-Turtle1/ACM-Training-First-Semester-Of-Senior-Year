#include<bits/stdc++.h>
using namespace std;
#define int long long
 
int const N = 2e5 + 10;
int const MOD = 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23;
int const INV2 = MOD / 2 + 1;

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
    int len = tr[u].r - tr[u].l + 1;
    if(lz1){
        tr[u].s1 = (tr[u].s1 + len * lz1 % MOD) % MOD;
        tr[u].lz1 = (tr[u].lz1 + lz1) % MOD;
    }
    if(lz2){
        int t = INV2 * lz2 % MOD;
        (tr[u].s2 += len * (tr[u].l + tr[u].r) % MOD * t % MOD) %= MOD;
        tr[u].lz2 = (tr[u].lz2 + lz2) % MOD;  
    }
}

void pushup(int u){
    tr[u].s1 = (tr[lc].s1 + tr[rc].s1) % MOD;
    tr[u].s2 = (tr[lc].s2 + tr[rc].s2) % MOD;
}

void pushdown(int u){
    work(lc, tr[u].lz1, tr[u].lz2);
    work(rc, tr[u].lz1, tr[u].lz2);
    tr[u].lz1 = tr[u].lz2 = 0;
}

// 建一颗空树
void build(int u, int l, int r){
    tr[u] = {l, r, 0, 0, 0, 0};
    if(l == r) return ;
    int mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(u);
}

// 把 [l, r] 范围修改为首项为 d1, 公差为 d2 的等差数列
// 按照这个方式传参 : modify(1, l, r, d1 - l * d2, d2)
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
        return (tr[u].s1 + tr[u].s2) % MOD;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    int res = 0;
    if(l <= mid) res = (res + ask(lc, l, r)) % MOD;
    if(r > mid) res = (res + ask(rc, l, r)) % MOD;
    return res % MOD;
}

int n, m;

void solve(){
    cin >> n;
    build(1, 1, n);
    for(int i = 1; i <= n; i ++){
        int x;
        cin >> x;
        modify(1, i, i, x, 0);
    }
    cin >> m;
    for(int i = 1; i <= m; i ++){ 
        int opt, l, r, k, d, M;
        cin >> opt >> l;
        if(opt == 1){
            cin >> r >> k >> d;
            modify(1, l, r, k - l * d, d);
        }
        else{ 
            cin >> r >> M;
            cout << ask(1, l, r) % M << '\n';
        } 
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
