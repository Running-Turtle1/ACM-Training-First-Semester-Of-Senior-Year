

#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1
int const N = 1e5 + 10;
struct node{
    int l, r, sum;
    int fg; // 修改懒标记
}tr[N * 4];

void pushup(int u){
    tr[u].sum = tr[lc].sum + tr[rc].sum;
}

void pushdown(int u){
    if(tr[u].fg){
        tr[lc].sum = tr[rc].sum = 0;
        tr[lc].fg = tr[rc].fg = 1;
        tr[u].fg = 0;
    }
}

void build(int u, int l, int r){
    if(l == r){
        tr[u] = {l, r, 1, 0};
        return ;
    }
    int mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(u);
}

void change(int u, int l, int r){
    if(l <= tr[u].l && r >= tr[u].r){
        tr[u].sum = 0;
        tr[u].fg = 1;
        return ;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    if(l <= mid) change(lc, l, r);
    if(r > mid) change(rc, l, r);
    pushup(u);
}

int ask(int u, int l, int r){
    if(l <= tr[u].l && r >= tr[u].r){
        return tr[u].sum;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    int res = 0;
    if(l <= mid) res += ask(lc, l, r);
    if(r > mid) res += ask(rc, l, r);
    pushup(u);
    return res;
}

class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<int> ans;
        build(1, 1, n);
        int q = queries.size();
        for(int i = 0; i < q; i ++){
            int u = queries[i][0] + 1, v = queries[i][1] + 1;
            if(u + 1 <= v - 1) change(1, u + 1, v - 1);
            ans.push_back(ask(1, 1, n) - 1);
        }
        return ans;
    }
};

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 

    return 0;
}
