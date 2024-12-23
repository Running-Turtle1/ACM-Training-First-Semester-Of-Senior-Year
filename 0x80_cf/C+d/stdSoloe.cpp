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
int lg[N], stA[20][N], stB[20][N];

int getgcd(int l, int r, int d)
{
    if(l > r) return 0;
    int k = lg[r - l + 1];
    if(d == 0) return __gcd(stA[k][l], stA[k][r - (1 << k) + 1]);
    if(d == 1) return __gcd(stB[k][l], stB[k][r - (1 << k) + 1]);
    return 0;
}

int SUFA[N], SUFB[N]; // 用于存储后缀 GCD
int PREA[N], PREB[N]; // 用于存储前缀 GCD

void solve()
{
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    for(int i = 1; i <= n; ++i) b[i] = read();
    for(int i = 1; i <= n; i ++){
        PREA[i] = __gcd(PREA[i - 1], a[i]);
        PREB[i] = __gcd(PREB[i - 1], b[i]);
    }
    for(int i = n; i >= 1; --i) {
        SUFA[i] = (i == n) ? a[i] : __gcd(SUFA[i + 1], a[i]);
        SUFB[i] = (i == n) ? b[i] : __gcd(SUFB[i + 1], b[i]);
    }
    SUFA[n + 1] = SUFB[n + 1] = 0;
    for(int i = 1; i <= n; ++i) stA[0][i] = a[i], stB[0][i] = b[i];

    for(int i = 1; i <= 19; ++i)
        for(int j = 1; j + (1 << i) - 1 <= n; ++j)
        {
            stA[i][j] = __gcd(stA[i - 1][j], stA[i - 1][j + (1 << (i - 1))]);
            stB[i][j] = __gcd(stB[i - 1][j], stB[i - 1][j + (1 << (i - 1))]);
        }
    ll ans = 0, sum = 0;
    int preA = 0, preB = 0;
    for(int l = 1; l <= n; ++l)
    {

        // int r = l;
        // while(r <= n && PREA[r] == PREA[l] && PREB[r] == PREB[l]){
        //     r ++;
        // }

        // l = r;

        int midA = a[l], sufA = SUFA[l + 1], midB = b[l], sufB = SUFB[l + 1];
        int last = l, L = l, R = n;
        while(L <= n)
        {
            while(L < R)
            {
                int mid = (L + R + 1) >> 1;
                if(midA == getgcd(l, mid, 0) && sufA == SUFA[mid + 1] && midB == getgcd(l, mid, 1) && sufB == SUFB[mid + 1]) L = mid;
                else R = mid - 1;
            }

            int tmp = __gcd(preA, __gcd(midB, sufA)) + __gcd(preB, __gcd(midA, sufB)), cnt = L - last + 1;
            cout << "seg: " << last<< ' ' << L << ' ' << tmp << '\n';
            // printf("l = %d, r = %d, preA = %d, midA = %d, sufA = %d, preB = %d, midB = %d, sufB = %d\n", l, L, preA, midA, sufA, preB, midB, sufB);
            // printf("tmp = %d, sum = %d\n", tmp, sum);
            if(tmp > ans) ans = tmp, sum = cnt;
            else if(tmp == ans) sum += cnt;
            ++L, R = n, last = L;
            midA = getgcd(l, L, 0), sufA = SUFA[L + 1], midB = getgcd(l, L, 1), sufB = SUFB[L + 1];
        }
        
        preA = PREA[l], preB = PREB[l];
    }
    printf("%lld %lld\n", ans, sum);
}

int main()
{
    lg[0] = -1;
    for(int i = 1; i <= 200000; ++i) lg[i] = lg[i >> 1] + 1;
    int T = read();
    while(T--) solve();
    return 0;
}