# P5937

> 每次给出 [l, r] 中有奇数还是偶数个 1，问你最小 x 可以满足 [1, x] 都是真话，x + 1 是假话

- `d[x]` 表示 1 的前缀和，[l, r ]中有奇数个 1，d[r]-d[l-1]$\equiv$ 1 mod 2; 偶数为 0

将 x-1 与 y 离散化，因为 数据范围太大。

离散化后维护他们到根节点的距离。只有两类域，奇数域和偶数域，且具备转化关系

```cpp
int const N = 1e6 + 10;

int n, m;
int p[N], d[N];
pair<int, int> ask[N];
int tmp[N];
string opt[N];

int find(int x){
    if(x == p[x]) return x;
    int t = find(p[x]);
    d[x] = (d[x] + d[p[x]]) % 2;
    return p[x] = t;
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= m; i ++){
        int x, y;
        cin >> x >> y >> opt[i];
        ask[i] = {x, y};
        tmp[2 * i - 1] = x;
        tmp[2 * i] = y;
    }
    sort(tmp + 1, tmp + 2 * m + 1);
    int sz = unique(tmp + 1, tmp + 2 * m + 1) - tmp - 1;
    for(int i = 1; i <= m; i ++){
        ask[i].first = lower_bound(tmp + 1, tmp + sz + 1, ask[i].first-1) - tmp;
        ask[i].second = lower_bound(tmp + 1, tmp + sz + 1, ask[i].second) - tmp;
    }
    for(int i = 1; i <= sz; i ++){
        p[i] = i;
        d[i] = 0;
    }
    for(int i = 1; i <= m; i ++){
        auto &[l, r] = ask[i];
        int pl = find(l), pr = find(r);
        if(pl != pr){
            p[pl] = pr;
            if(opt[i] == "odd"){
                d[pl] = (d[r] - d[l] + 1 + 2) % 2;
            }
            else{
                d[pl] = (d[r] - d[l] + 2) % 2;
            }
        }
        else{
            if(opt[i] == "odd"){
                if((d[r] - d[l] + 2) % 2 == 0){
                    cout << i - 1;
                    return ;
                }
            }
            else{
                if((d[r] - d[l] + 2) % 2 == 1){
                    cout << i - 1;
                    return ;
                }
            }
        }
    }
    cout<<m;
}
```

好像不是很懂这道题啊，----，脑子不够用了
