对于 $x=1$，令 $a=1$ 使得 $x=a^b$ 对于所有不小于 2 的整数 $b$ 都成立，因此 1 满足问题陈述中的条件。
由于这种特殊情况处理起来很尴尬，我们将计算满足条件的所有大于或等于 2 的整数。

首先，考虑一个整数如何表示为 $a^b$。

例如，考虑一个整数 $x=64=2^6$。

- $x$ 可以通过令 $a=2^3$ 表示为 $a^2$。
- $x$ 可以通过令 $a=2^2$ 表示为 $a^3$。
- $x$ 可以通过令 $a=2^1$ 表示为 $a^6$。

再考虑另一个整数 $x=2985984 = 2^{12} \times 3^6$。

- $x$ 可以通过令 $a=(2^6 \times 3^3)$ 表示为 $a^2$。
- $x$ 可以通过令 $a=(2^4 \times 3^2)$ 表示为 $a^3$。
- $x$ 可以通过令 $a=(2^2 \times 3^1)$ 表示为 $a^6$。

一般来说，设 $x=p^lq^mr^n \dots$ 是一个整数 $x$ 的素因数分解。那么：

- 对于 $l,m,n,\dots$ 的一个公约数 $k$，可以令 $a=p^{(l/k)}q^{(m/k)}r^{(n/k)} \dots$ 以表示为 $a^k$。

因此，结果表明，如果且仅当 $b$ 是 $g$ 的一个不小于 2 的约数，其中 $g = \gcd(l,m,n,\dots)$，则所需的表示 $x=a^b$ 是可能的。

---

接下来，我们计算对于一个固定的 $b$，可能的整数 $a$。
具体来说，对于每个 $b$，找到满足 $a^b \le N$ 的最大 $a$ 即可。
由于 $2^{60} > 10^{18}$，在此问题的约束下，只需考虑范围 $2 \le b < 60$。
我们可以对每个 $b$ 进行二分搜索 $a$。
注意 $a^b$ 可能会溢出；为了避免这个问题，例如，因为 $b$ 很小，可以通过朴素地将其乘 $b$ 次来找到 $b$ 的幂，每次将 $a$ 相乘时，使用 double 类型等估算结果，以便在估算值足够大时停止计算。

---

现在我们已经得到了所有 $b=2,3,\dots,59$ 的整数表示为 $a^b$ 的个数，让我们计算它们的并集而不重复计数。

我们使用[除数上的容斥原理（关于日文文章）](https://blog.hamayanhamayan.com/entry/2017/04/17/161345)来求和。
对于一个整数 $x=p^lq^mr^n \dots$ 的素因数分解，我们已经表明如果且仅当 $b$ 是 $g=\gcd(l,m,n,\dots)$ 的大于等于 2 的约数，则存在一个表示 $x=a^b$。
这里，设 $g$ 是 $P^LQ^MR^N \dots $ 的素因数分解。$x$ 可以通过以下方式精确计数：

- 添加 $b=P, Q, R, \dots$ 的情况（其中 $b$ 是 $g$ 的一个素因数的乘积）。
- 减去 $b=PQ, PR, \dots, QR, \dots$ 的情况（其中 $b$ 是 $g$ 的两个素因数的乘积）。
- 添加 $b=PQR, \dots$ 的情况（其中 $b$ 是 $g$ 的三个素因数的乘积）。
- $\vdots$

证明可以与普通的容斥原理证明相同。

因此，可以通过以下方式计算不重复或遗漏的符合条件的整数个数。

- 如果 $b$ 有一个平方因数（如果 $b$ 有多个素因数），忽略它。
- 否则，如果 $b$ 有奇数个素因数，添加它。
- 否则，如果 $b$ 有偶数个素因数，减去它。

通过实现这些步骤，可以在总共约 $O(\log^3 N)$ 时间内解决问题。

```cpp
#include<bits/stdc++.h>

using namespace std;

vector<long long> pfact(long long x){
  vector<long long> res;
  for(long long i=2;i*i<=x;i++){
    while(x%i==0){
      res.push_back(i);
      x/=i;
    }
  }
  if(x>1){res.push_back(x);}
  return res;
}

long long safe_pow(long long a,long long b){
  long long res=1;
  for(long long i=0;i<b;i++){
    double dres=res;
    dres*=a;
    if(dres>2e18){return 2e18;}
    res*=a;
  }
  return res;
}

int main(){
  long long n;
  cin >> n;
  long long res=0;
  for(long long b=2;b<60;b++){
    long long l=2,r=2e9;
    while(l<=r){
      long long t=(l+r)/2;
      if(safe_pow(t,b)>n){r=t-1;}
      else{l=t+1;}
    }
    // a = [2,r] satisfy a^b <= n
    vector<long long> pf=pfact(b);
    bool same=false;
    for(long long i=1;i<pf.size();i++){
      if(pf[i-1]==pf[i]){same=true; break;}
    }
    if(same){continue;}
    if(pf.size()%2){res+=(r-1);}
    else{res-=(r-1);}
  }
  res++; // count 1
  cout << res << "\n";
  return 0;
}
```
