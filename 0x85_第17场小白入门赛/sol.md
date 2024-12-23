# 第 17 场小白入门赛

## 2 北伐军费

发现每次选大的更优，所以可以排序之后，先手取右边，后手取左边。

实际发现，对于 $A-B$ 的结果来说，后手对于这个式子的贡献是 $--a_i$ ，也就是 $a_i$ ，实际答案就是数组之和。

```cpp
void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++) cin >> a[i]; 
    cout << accumulate(a + 1, a + n + 1, 0LL) << '\n';
}
```

## 4 三顾茅庐

找规律，对于 $x\leq y$ 的情况 $2$ 次一循环。

对于 $x>y$ 的情况，$x$ 每次回减 $y$ 直到用完 $k$ 次机会或者 $x<=y$ 了，实际就是取模的过程。

```cpp
void solve(){
    int x, y, k;
    cin >> x >> y >> k;
    if(!y){
        cout << x << '\n';
        return ;
    }
    if(x <= y){
        cout << ((k & 1) ? y - x : x) << '\n';
    }
    else{
        int t = (x / y);
        if(k > t){
            k -= t;
            x %= y;
            cout << ((k & 1) ? y - x : x) << '\n';
        }
        else{
            cout << x - k * y << '\n';
        }
    }
}
```

## 3 挑选武将

思路比较简单，将每个城池出现几个武将排序，从前往后枚举，只要当前选过的加上剩余的 $\geq k$ 即可。

蓝桥的 oj 比较垃圾，会 RE 只会返回 WA，非常不智能。

```cpp
void solve(){
    cin >> n >> k;
    for(int i = 1; i <= n; i ++){
        cin >> x;
        a[x] ++;
    }
    vector<int> vc;
    for(int i = 1; i <= 100000; i ++){
        if(a[i]) vc.push_back(a[i]);
    } 
    sort(vc.begin(), vc.end());
    vector<int> sum(vc.size());
    sum[0] = vc[0];
    for(int i = 1; i < vc.size(); i ++) sum[i] = vc[i] + sum[i - 1];
    auto ask = [&] (int l, int r){
        if(l > r) return 0LL;
        if(!l) return sum[r];
        return sum[r] - sum[l - 1];
    };
    int res = 0;
    for(int i = 0; i < vc.size() && (i + 1) <= k; i ++){
        if((i + 1) + ask(i + 1, vc.size() - 1) >= k) res = i + 1;
    }
    cout << res << '\n';
}
```

## 5 逆天改命

> 给你一个长度为 $n$ 的数组 $b$ ，你有一个 $\forall a_i=0$ 的数组 $a$ 。
> 
> 可以执行以下两种操作 :
> 
> 1，选取 [l, r] 区间，这个区间必须存在 $a_i=0$ ，令所有数 + 1
> 
> 2，选取 [l, r] 区间，这个区间不存在 $a_i=0$ , 令所有数 - 1

很有意思的一道题目。

发现对于数组操作的过程中，一定不可能让最小值 $\geq 2$ 。

因为最后一个 $0$ ，只能被选一次。

只要有 $01$ ，就能构造。

```cpp
void solve(){
    int n, x, fg = 0;
    cin >> n;
    while(n --){
        cin >> x;
        fg |= (x == 0 || x == 1);
    }
    cout << (fg ? "YES" : "NO") << '\n';
}
```

## 6 智算士气

$m=p_1^{c_1}\times p_2^{c_2}\times \cdots \times p_i ^{c_i}$ 。

对于每一位，至少存在一个数为 $p_i^{c_i}$ ，正难则反，第 $i$ 位共有 $(c_i+1)^n-c_i^n$ 种方案，考虑所有位，答案为 $\prod _i (c_i+1)^n-c_i^n$ 。

```cpp
map<int, int> pm;

void solve(){ 
    cin >> n >> m;

    for(int i = 2; i <= m / i; i ++){
        while(m % i == 0){
            pm[i] ++;
            m /= i;
        }
    }   
    if(m > 1) pm[m] ++;
    int res = 1;
    for(auto [x, y] : pm){ 
        res *= ksm(y + 1, n, mod) - ksm(y, n, mod);
        res %= mod;
        if(res < 0) res += mod;
    }
    cout << res;
}
```
