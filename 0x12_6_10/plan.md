复习安排 don't care ×

去看看乌龟

晚上去吃饭

C#安排一下

创新创业先整上吧。 √

牛客周赛

Sora

---

昨天出去玩了，跟房红奕交流一下感情，今天晚上还要出去吃饭，我想了一下还是去吧，毕竟自己因此节省了更多时间。

那么上午的话，先把之前 atcoder 的 F 题补了，安排一下牛客周赛，然后开始期末复习吧。

做完了 F

Sora ？

---

- F

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1

int const mod = 998244353;
int const N = 2e5 + 10;
struct TreeNode{
    int l, r;
    int sumA, sumB, sumAmulB; // 维护信息
    int addA, addB; // 区间加懒标记
} tr[N * 4];

int a[N], b[N];

// 向上更新
void pushup(int u){
    tr[u].sumA = (tr[lc].sumA + tr[rc].sumA) % mod;
    tr[u].sumB = (tr[lc].sumB + tr[rc].sumB) % mod;
    tr[u].sumAmulB = (tr[lc].sumAmulB + tr[rc].sumAmulB) % mod;
}

// 向下更新
void pushdown(int u){
    if(tr[u].addA || tr[u].addB){
        int llen = tr[lc].r - tr[lc].l + 1;
        tr[lc].sumAmulB = (tr[lc].sumAmulB + tr[u].addA * tr[u].addB % mod * llen % mod + tr[u].addA * tr[lc].sumB % mod + tr[u].addB * tr[lc].sumA % mod) % mod;
        tr[lc].sumA = (tr[lc].sumA + tr[u].addA * llen % mod) % mod;
        tr[lc].sumB = (tr[lc].sumB + tr[u].addB * llen % mod) % mod;
        tr[lc].addA = (tr[lc].addA + tr[u].addA) % mod;
        tr[lc].addB = (tr[lc].addB + tr[u].addB) % mod;

        int rlen = tr[rc].r - tr[rc].l + 1;
        tr[rc].sumAmulB = (tr[rc].sumAmulB + tr[u].addA * tr[u].addB % mod * rlen % mod + tr[u].addA * tr[rc].sumB % mod + tr[u].addB * tr[rc].sumA % mod) % mod;
        tr[rc].sumA = (tr[rc].sumA + tr[u].addA * rlen % mod) % mod;
        tr[rc].sumB = (tr[rc].sumB + tr[u].addB * rlen % mod) % mod;
        tr[rc].addA = (tr[rc].addA + tr[u].addA) % mod;
        tr[rc].addB = (tr[rc].addB + tr[u].addB) % mod;

        tr[u].addA = tr[u].addB = 0;
    }
}

void buildTree(int u, int l, int r){
    tr[u] = {l, r, a[l], b[l], a[l] * b[l] % mod, 0, 0};
    if(l == r) return ;
    int mid = l + r >> 1;
    buildTree(lc, l, mid);
    buildTree(rc, mid + 1, r);
    pushup(u);
}

void SegmentAddOfA(int u, int l, int r, int v){
    if(l <= tr[u].l && r >= tr[u].r){
        int len = tr[u].r - tr[u].l + 1;
        tr[u].sumA = (tr[u].sumA + len * v % mod) % mod;
        tr[u].sumAmulB = (tr[u].sumAmulB + v * tr[u].sumB % mod) % mod;
        tr[u].addA = (tr[u].addA + v) % mod;
        return ;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    if(l <= mid) SegmentAddOfA(lc, l, r, v);
    if(r > mid) SegmentAddOfA(rc, l, r, v);
    pushup(u);
}

void SegmentAddOfB(int u, int l, int r, int v){
    if(l <= tr[u].l && r >= tr[u].r){
        int len = tr[u].r - tr[u].l + 1;
        tr[u].sumB = (tr[u].sumB + len * v % mod) % mod;
        tr[u].sumAmulB = (tr[u].sumAmulB + v * tr[u].sumA % mod) % mod;
        tr[u].addB = (tr[u].addB + v) % mod;
        return ;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    if(l <= mid) SegmentAddOfB(lc, l, r, v);
    if(r > mid) SegmentAddOfB(rc, l, r, v);
    pushup(u);
}

int AskSegmentSum(int u, int l, int r){
    if(l <= tr[u].l && r >= tr[u].r){ // 覆盖则返回
        return tr[u].sumAmulB;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    int sum = 0;
    if(l <= mid) sum = (sum + AskSegmentSum(lc, l, r)) % mod;
    if(r > mid) sum = (sum + AskSegmentSum(rc, l, r)) % mod;
    return sum;
}

int n, q;

void solve(){
    cin >> n >> q;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    for(int i = 1; i <= n; i ++){
        cin >> b[i];
    }
    buildTree(1, 1, n); // 建树
    while(q --){
        int opt, l, r, x;
        cin >> opt >> l >> r;
        if(opt == 1){
            cin >> x;
            SegmentAddOfA(1, l, r, x);
        }
        else if(opt == 2){
            cin >> x;
            SegmentAddOfB(1, l, r, x);
        }
        else{
            cout << AskSegmentSum(1, l, r) << '\n';
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

幸亏有 chatgpt，要不 debug 得一上午。

首先取模 chatgpt 写的很快，其次线段树我忘了下传懒标记，chatgpt 也能实现。
