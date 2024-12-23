#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    const static int mod = 10000; // 基数
    const static int DLEN = 4;     // 每个整数的位数
    int a[600], len;

    BigInt() {
        memset(a, 0, sizeof(a));
        len = 1; // 默认长度为1
    }

    BigInt(int v) {
        memset(a, 0, sizeof(a));
        len = 0;
        do {
            a[len++] = v % mod; // 每个元素存储v的mod
            v /= mod;
        } while (v);
    }

    BigInt(const char s[]) {
        memset(a, 0, sizeof(a));
        int L = strlen(s);
        len = L / DLEN;
        if (L % DLEN) len++;
        int index = 0;
        for (int i = L - 1; i >= 0; i -= DLEN) {
            int t = 0;
            int k = i - DLEN + 1;
            if (k < 0) k = 0;
            for (int j = k; j <= i; j++)
                t = t * 10 + s[j] - '0';
            a[index++] = t; // 将每个子串转为整数存储
        }
    }

    BigInt operator +(const BigInt &b) const {
        BigInt res;
        res.len = max(len, b.len);
        for (int i = 0; i <= res.len; i++)
            res.a[i] = 0;

        for (int i = 0; i < res.len; i++) {
            res.a[i] += ((i < len) ? a[i] : 0) + ((i < b.len) ? b.a[i] : 0);
            res.a[i + 1] += res.a[i] / mod; // 进位处理
            res.a[i] %= mod;
        }
        
        if (res.a[res.len] > 0) res.len++;
        return res;
    }

    BigInt operator *(const BigInt &b) const {
        BigInt res;
        for (int i = 0; i < len; i++) {
            int up = 0; // 进位
            for (int j = 0; j < b.len; j++) {
                int temp = a[i] * b.a[j] + res.a[i + j] + up;
                res.a[i + j] = temp % mod; // 存储当前位
                up = temp / mod; // 更新进位
            }
            if (up != 0)
                res.a[i + b.len] = up; // 处理最后一位进位
        }
        res.len = len + b.len;
        while (res.a[res.len - 1] == 0 && res.len > 1) res.len--; // 去掉前导零
        return res;
    }

    void output() {
        printf("%d", a[len - 1]); // 输出最高位
        for (int i = len - 2; i >= 0; i--) {
            printf("%04d", a[i]); // 输出低位
        }
        printf("\n");
    }
};


void solve(){
    
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
