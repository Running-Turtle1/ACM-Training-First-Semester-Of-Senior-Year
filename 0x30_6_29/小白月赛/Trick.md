## 题目链接

[F-parent 树上启发式合并_牛客小白月赛97 (nowcoder.com)](https://ac.nowcoder.com/acm/contest/85347/F)

## 题解

不同字符串长度总和不超过 $10^4$ ，最多多少种长度呢 ？

设为 $x$ ，就是 $1+2+\cdots+x=\frac{x*(x+1)}{2}\leq 10^4$ 

其实最多也就 140 种长度，将询问离线，对于每个长度更新一下答案 map 就行了，就多更新 140 次，大约 $O(140n)$ 吧。（当然 map 存多了有点问题，加个 uset 判定就不超时了）

感觉没啥问题，$653ms/2000ms$ 过了。

## Analysis

- 可能数据弱了，只用 umap 超时了，只 push_back 查询元素（用 uset 判定）就对了

- 关键就是对于这种询问字符串长度总和有限的维护题，一般来说，其实字符串的总种类数或者说长度种类数是很有限制的，实际上做起来就偏暴力了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int const N = 1e5 + 10;
int const P = 13331;
typedef unsigned long long ull;
ull h[N], p[N];

int n, q;
int len;
string s;

void init(){
    p[0] = 1;
    for(int i = 1; i <= n; i ++){
        p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + s[i];
    }
}
ull ask(int l, int r){
    return h[r] - h[l - 1] * p[r - l + 1];
}

ull cal(string &t){
    ull res = 0;
    for(int i = 0; i < t.size(); i ++){
        res = res * P + t[i];
    }
    return res;
}

struct query{
    ull t;
    int k;
    int id;
    size_t len;
}Q[N];
int ans[N];

unordered_set<ull> st;
unordered_map<ull, vector<int> > mp;
void updateMap(int len){
    mp.clear();
    for(int i = 1; i + len - 1 <= n; i ++){
        int r = i + len - 1;
        if(st.count(ask(i, r))){
            mp[ask(i, r)].push_back(r);
        }
    }
}

void solve(){
    cin >> n >> q >> s;
    s = ' ' + s;
    init(); // 初始化哈希
    for(int i = 1; i <= q; i ++) {
        string t;
        int k;
        cin >> t >> k;
        Q[i] = {cal(t), k, i, t.size()};
        st.insert(Q[i].t);
    }
    sort(Q + 1, Q + q + 1, [] (query &a, query & b){
        return a.len < b.len;
    });
//     for(int i = 1; i <= q; i ++){
//         auto &[t, k, id, len] = Q[i];
//     }
    size_t nowLen = 0;
    for(int i = 1; i <= q; i ++){
        auto &[t, k, id, len] = Q[i];
        if(nowLen != len){
            nowLen = len;
            updateMap(len);
        }
        if(mp[t].size() < k){
            ans[id] = -1;
        }
        else{
            ans[id] = mp[t][k - 1];
        }
    }
    for(int i = 1; i <= q; i ++){
        cout << ans[i] << '\n';
    }
}   

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}

```
