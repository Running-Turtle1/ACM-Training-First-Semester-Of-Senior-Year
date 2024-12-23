- div3 E 计划，看心情
- vp div2 + 补题 + D + E （D 优先做了） + 只做 D
- [P5973 [PA2013] Iloczyn - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P5973)
- LC 周赛
- 并查集题目 还剩两个 ds 的简单并查集题目

---

- 计蒜客 -- 停止
- 根号分支 -- 停止

----

昨晚pj了，直接失眠，起来一点精神没有，没怎么做很难的题，刚才看了一下提高组的 A 题，感觉是出题人错了。

![](.\1.png)

![](.\2.png)

计蒜客，我之所以打，是因为有的题目很好，所以对于不好的应该迅速跳过。

---

[P1197 [JSOI2008] 星球大战 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P1197)

很简单就能想到逆序维护，但是自己往回加星期的时候脑子抽了，维护连通块数量写得很麻烦。

实际上，不在同一个连通块的两个连通块合并，就会少一个连通块，很显然，很显然，。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 4e5 + 10;

int n, m, k, p[N];

unordered_set<int> mp;
vector<int> e[N];

int ans[N];
int idx[N];

int find(int x){
    if(x == p[x]) return p[x];
    return p[x] = find(p[x]);
}

void solve(){
    cin >> n >> m;
    for(int i = 0; i < n; i ++){
        p[i] = i;
    }
    for(int i = 0; i < m; i ++){
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    cin >> k;
    for(int i = 0; i < k; i ++){
        cin >> idx[i];
        mp.insert(idx[i]); // 灭亡星球 id
    }

    for(int i = 0; i < n; i ++){
        if(mp.count(i)) continue; // i 必须活下来
        for(int j = 0; j < e[i].size(); j ++){
            int v = e[i][j];
            if(mp.count(v)) continue; // v 也是
            p[find(i)] = find(v);
        }
    }
    ans[k] = 0;
    for(int i = 0; i < n; i ++){
        if(p[i] == i && mp.count(i) == false) ans[k] ++;
    }

    // unordered_set<int> add;
    for(int i = k - 1; i >= 0; i --){
        int id = idx[i]; // 复活的星球
    //    unordered_set<int> tmp;
        ans[i] = ans[i + 1] + 1;
        for(auto &v : e[id]){
            if(mp.count(v)) continue;
            int pid = find(id), pv = find(v);
            if(pid != pv){
                p[pv] = p[pid];
                ans[i] --;
            }    
    //        if(mp.count(v) == false) tmp.insert(v);
    //        p[find(v)] = find(id);
    //        add.insert(find(v));
        }
        mp.erase(id);
    //    ans[i] = ans[i + 1] - tmp.size() + 1;
    }
    for(int i = 0; i <= k; i ++){
        cout << ans[i] << '\n';
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}

// 倒着做，最开始所有星球被摧毁了，算一下连通块数量 res；
// 之后相当于加边，看看边涉及了多少连通块，假设涉及了 x 个，res = res - x + 1
```

先加去掉毁灭点的边，然后逐个往回加回来就行了。
