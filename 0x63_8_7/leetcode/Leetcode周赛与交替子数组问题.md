## LC3242

类和对象题，用 `map` 记录一下位置，模拟即可

```cpp
class neighborSum {
public:
    int n, m;
    vector<vector<int>> grid;
    map<int, pair<int, int> > pos;
    int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    int dy[8] = {0, 0, 1, -1, -1, 1, -1, 1};
    neighborSum(vector<vector<int>>& grids) {
        grid = grids;
        n = grid.size(), m = grid[0].size();
        for(int i = 0; i < n; i ++){
            for(int j = 0; j < m; j ++){
                pos[grid[i][j]] = {i, j};
            }
        }
    }
        
    int adjacentSum(int value) {
        auto &[x, y] = pos[value];
        int res = 0;
        for(int i = 0; i < 4; i ++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m){
                res += grid[nx][ny];
            }
        }
        return res;
    }
    
    int diagonalSum(int value) {
        auto &[x, y] = pos[value];
        int res = 0;
        for(int i = 4; i < 8; i ++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < m){
                res += grid[nx][ny];
            }
        }
        return res;
    }
};

/**
 * Your neighborSum object will be instantiated and called as such:
 * neighborSum* obj = new neighborSum(grid);
 * int param_1 = obj->adjacentSum(value);
 * int param_2 = obj->diagonalSum(value);
 */
```

## LC3243

$n$ 比较小，每次加边之后 `bfs` 即可

```cpp
class Solution {
public:
     
    vector<int> e[510];
    int d[510];
    int bfs(int n){
        for(int i = 0; i < n; i ++) d[i] = -1;
        d[0] = 0;
        queue<int> q;
        q.push(0);
        while(q.size()){
            auto t = q.front(); 
            q.pop();
            for(auto &v : e[t]){
                if(d[v] == -1){
                    d[v] = d[t] + 1;
                    q.push(v);
                }
            }
        }
        return d[n - 1];
    }
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        for(int i = 0; i < n - 1; i ++){
            e[i].push_back(i + 1);
        }
        vector<int> ans;
        for(int i = 0; i < queries.size(); i ++){
            int u = queries[i][0], v = queries[i][1];
            e[u].push_back(v);
            ans.push_back(bfs(n));
        }
        return ans;
    }
};
```

## LC3244

观察到所有路线不交叉，只有覆盖和单点相交和不相交三种关系，每个路线 $[l,r]$ 相当于去掉 $(l,r)$ 这些点，线段树维护即可。

```cpp
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
    tr[u] = {l, r, 1, 0};
    if(l == r){
        
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
 
```

## LC3206

每个交替组都有一个起点，枚举这个起点即可。

因为长度固定为 $3$ ，我们枚举交替组的左端点，检验即可

```cpp
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors) {
        int n = colors.size();
        int res = 0;
        for(int i = 0; i < n; i ++){
            int p1 = (i + 1) % n;
            int p2 = (i + 2) % n;
            if(colors[p1] != colors[i] && colors[p1] != colors[p2]) res ++;
        } 
        return res;
    }
};
```

## LC3101

还是枚举左端点，双指针找到每段最长的交替子数组。

这段子数组的每一段子数组都是交替子数组，假设一共有 $x$ 段交替子数组，$res=\sum_{i=1}^x \frac{len_i*(len_i +1)}{2}$ 

```cpp
class Solution {
public:
    long long countAlternatingSubarrays(vector<int>& nums) {
        int n = nums.size();
        long long res = 0;
        for(int i = 0; i < n; i ++){
            int j = i;
            while(j + 1 < n && nums[j + 1] != nums[j]) j ++;
            long long t = j - i + 1;
            res += t * (t + 1) / 2;
            i = j;
        }
        return res;
    }
};
```

## LC3208

复制一遍数组，同样枚举左端点，对于每个左端点 $[0,n)$ ，看看右端点与左端点的长度之差是否 $\geq$ k，注意右端点的取值范围是 $[i,2n)$ 

```cpp
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int n = colors.size();
        int res = 0;
        for(int i = 0, j = 0; i < n; i ++){
            if(j < i) j = i;
            while(j + 1 < 2 * n && colors[(j + 1) % n] != colors[j % n]) j = (j + 1);
            cout << i << ' ' << j << '\n';
            if((j - i + 1) >= k) res ++;
        }
        return res;
    }
};
```

## LC3245

环形数组，动态修改颜色，动态询问长度为 $k$ 的交替子数组有多少个。

用 `set` 维护每个 $color_i = color_{i+1}$  的地方，两个树状数组分别维护长度 $x$ 的总贡献以及长度 $x$ 的出现次数。

对于修改，维护 `set` 和树状数组即可。

```cpp
class Solution {
public:
    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size();

        int tr[n + 1][2];
        memset(tr, 0, sizeof tr);
        auto add = [&] (int id, int pos, int val){
            for(int i = pos; i <= n; i += i & -i) tr[i][id] += val;
        };
        auto ask = [&] (int id, int l, int r) {
            int res = 0;
            for(int i = r; i; i -= i & -i) res += tr[i][id];
            for(int i = l - 1; i; i -= i & -i) res -= tr[i][id];
            return res;
        };

        // k = 1 表示往结束点 set 里加入新结束点 pos
        // k = -1 表示从结束点 set 里删除结束点 pos
        // L 和 R 是 pos 左边和右边最近的其它结束点
        auto update = [&] (int l, int r, int pos, int k){
            int old = (r - l + n) % n;
            if(!old) old = n;
            add(0, old, -k * old);
            add(1, old, -k);

            int len = (pos - l + n) % n;
            if(!len) len = n;
            add(0, len, k * len);
            add(1, len, k);

            len = (r - pos + n) % n;
            if(!len) len = n;
            add(0, len, k * len);
            add(1, len, k);
        };

        set<int> st;
        auto ins = [&] (int pos) {
            if(st.empty()){
                st.insert(pos);
                add(0, n, n), add(1, n, 1);
            }
            else{
                auto it = st.insert(pos).first;
                int l = (it == st.begin() ? *st.rbegin() : *prev(it));
                int r = (next(it) == st.end() ? *st.begin() : *next(it));
                update(l, r, pos, 1);
            }
        };

        auto del = [&] (int pos) {
            if(st.size() == 1){
                st.erase(st.find(pos));
                add(0, n, -n), add(1, n, -1);
            }
            else{
                auto it = st.erase(st.find(pos));
                // 找到左右两个最近的其它结束点
                int L = (it == st.begin() ? *prev(st.end()) : *prev(it));
                int R = (it == st.end() ? *(st.begin()) : *it);
                update(L, R, pos, -1); 
            }
        };

        for (int i = 0; i < n; i++) if (colors[i] == colors[(i + 1) % n]) ins(i);
        
        vector<int> ans;
        for (auto &qry : queries) {
            if (qry[0] == 1) {
                if (st.empty()) ans.push_back(n);
                else {
                    // 因为树状数组维护的是小于等于 s 的总和
                    // 要求大于等于 s 的总和，可以转为“所有元素之和，减去小于等于 s - 1 的总和”
                    int sm = ask(0, qry[1], n);
                    int cnt = ask(1, qry[1], n);
                    ans.push_back(sm - cnt * qry[1] + cnt);
                }
            } else {
                // 修改 idx 的颜色，只影响 idx - 1 和 idx 是否成为结束点
                int idx = qry[1], col = qry[2];
                int prv = (idx - 1 + n) % n, nxt = (idx + 1) % n;
                // 回撤旧情况
                if (colors[prv] == colors[idx]) del(prv);
                if (colors[idx] == colors[nxt]) del(idx);
                // 计算新情况
                colors[idx] = col;
                if (colors[prv] == colors[idx]) ins(prv);
                if (colors[idx] == colors[nxt]) ins(idx);
            }
        }
        return ans;
 
    }
};
```
