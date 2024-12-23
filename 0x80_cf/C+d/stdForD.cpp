#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long

int read()
{
    int x = 0; bool f = false; char c = getchar();
    while(c < '0' || c > '9') f |= (c == '-'), c = getchar();
    while(c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c & 15), c = getchar();
    return f ? -x : x;
}

const int N = 2e5 + 5;
int n, a[N], b[N];
int preA[N], preB[N], SUFA[N], SUFB[N];
vector< pair<int, int> > sufA, sufB, midA, midB;
vector< pair<int, int> > tmp;
int lg[N], stA[20][N], stB[20][N];

int gcd(int x, int y)
{
    if(!y) return x;
    return gcd(y, x % y);
}

void init()
{
    for(int i = 1; i <= n; ++i) stA[0][i] = a[i], stB[0][i] = b[i];
    for(int i = 1; i <= 19; ++i)
        for(int j = 1; j + (1 << i) - 1 <= n; ++j)
            stA[i][j] = gcd(stA[i - 1][j], stA[i - 1][j + (1 << (i - 1))]),
            stB[i][j] = gcd(stB[i - 1][j], stB[i - 1][j + (1 << (i - 1))]);
}

int getgcd(int l, int r, int d)
{
    if(l > r) return 0;
    int k = lg[r - l + 1];
    if(d == 0) return gcd(stA[k][l], stA[k][r - (1 << k) + 1]);
    else return gcd(stB[k][l], stB[k][r - (1 << k) + 1]);
}

int sta[N], top, vis[N];

void solve()
{
    // 预处理信息
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = read(), preA[i] = gcd(a[i], preA[i - 1]);
    for(int i = 1; i <= n; ++i) b[i] = read(), preB[i] = gcd(b[i], preB[i - 1]);
    SUFA[n + 1] = SUFB[n + 1] = 0;
    for(int i = n; i >= 1; --i) SUFA[i] = gcd(a[i], SUFA[i + 1]), SUFB[i] = gcd(b[i], SUFB[i + 1]);
    init();
    sufA.clear(), sufB.clear(), midA.clear(), midB.clear();
    int ans = 0;
    ll sum = 0;
 
    sufA.emplace_back(pair<int, int>(a[n], n));
    sufB.emplace_back(pair<int, int>(b[n], n));
    midA.emplace_back(pair<int, int>(a[n], n));
    midB.emplace_back(pair<int, int>(b[n], n));
    for(int l = n - 1; l >= 0; --l)
    {
        for(auto [val, id] : sufA) if(!vis[id - 1]) sta[++top] = id - 1, vis[id - 1] = 1;
        for(auto [val, id] : sufB) if(!vis[id - 1]) sta[++top] = id - 1, vis[id - 1] = 1;
        for(auto [val, id] : midA) if(!vis[id]) sta[++top] = id, vis[id] = 1;
        for(auto [val, id] : midB) if(!vis[id]) sta[++top] = id, vis[id] = 1;
        sort(sta + 1, sta + top + 1);
        if(!vis[n]) sta[++top] = n, vis[n] = 1;
        sta[++top] = n + 1;

        for(int i = 1; i < top; ++i)
        {
            int r = sta[i];
            if(r <= l) continue;
            int MIDA = getgcd(l + 1, r, 0), MIDB = getgcd(l + 1, r, 1);
            int ansA = gcd(preA[l], gcd(MIDB, SUFA[r + 1])), ansB = gcd(preB[l], gcd(MIDA, SUFB[r + 1]));
            if(ansA + ansB > ans){ ans = ansA + ansB, sum = sta[i + 1] - sta[i]; }
            else if(ansA + ansB == ans) sum += sta[i + 1] - sta[i];
        }

        for(int i = 1; i < top; ++i) vis[sta[i]] = 0;
        top = 0;

        if(!l) continue;
        pair<int, int> flag1 = *--sufA.end();
        int flag2 = gcd(flag1.first , a[l]); 
        if(flag1.first == flag2) sufA.pop_back();
        sufA.emplace_back(pair<int, int>(flag2, l));

        flag1 = *--sufB.end();
        flag2 = gcd(flag1.first , b[l]);
        if(flag1.first == flag2) sufB.pop_back();
        sufB.emplace_back(pair<int, int>(flag2, l));

        tmp.emplace_back(pair<int, int>(a[l], l));
        for(auto [val, id] : midA)
        {
            int newval = gcd(val, a[l]);
            if(newval == (*--tmp.end()).first ) continue;
            else tmp.emplace_back(pair<int, int>(newval, id));
        }
        midA = tmp, tmp.clear();

        tmp.emplace_back(pair<int, int>(b[l], l));
        for(auto [val, id] : midB)
        {
            int newval = gcd(val, b[l]);
            if(newval == (*--tmp.end()).first ) continue;
            else tmp.emplace_back(pair<int, int>(newval, id));
        }
        midB = tmp, tmp.clear();
    }
    printf("%d %lld\n", ans, sum);
}

int main()
{
    lg[0] = -1;
    for(int i = 1; i <= 200000; ++i) lg[i] = lg[i >> 1] + 1; // 预处理 ST 表所需要的 \log
    int T = read();
    while(T--) solve();
    return 0;
}