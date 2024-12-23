# 计算 n! 中包含质因子 p 的个数

有公式 :

$$
num=\lfloor\frac{x}{p}\rfloor + \lfloor\frac{x}{p^2}\rfloor 
+ \lfloor\frac{x}{p^3}\rfloor + \cdots
$$

$\lfloor\frac{x}{p^k}\rfloor$ 相当于 1 到 n 中 $p^k$  的倍数的个数。公式中只累加一遍是因为 $p^{k-1}$  这些已经在上一次被加过了。比如求 8！中 2 的个数，1 到 8中 2 的倍数有2，4，6，8 = 8 / 2 = 4个，他们共有 4 个 2；$2^2$ = 4的倍数有4，8 = 8 / 4 = 2个，相当于贡献了2个4 == 4个2，但上一轮4和8各贡献了一个2，因此本轮只算贡献了2个2（本轮算出来几个数就算贡献了几个p）。

```cpp
void cal(int n){
    int res = 0;
    while(n){
        res += n /= 5;
    }
    cout << res << '\n';
}
```
