struct BigInt {
    int a[LEN];

    BigInt(int x = 0) : a{} {
        for (int i = 0; x; i++) {
            a[i] = x % 10;
            x /= 10;
        }
    }

    BigInt &operator*=(int x) {
        for (int i = 0; i < LEN; i++) {
            a[i] *= x;
        }
        for (int i = 0; i < LEN - 1; i++) {
            a[i + 1] += a[i] / 10;
            a[i] %= 10;
        }
        return *this;
    }

    BigInt &operator/=(int x) {
        for (int i = LEN - 1; i >= 0; i--) {
            if (i) {
                a[i - 1] += a[i] % x * 10;
            }
            a[i] /= x;
        }
        return *this;
    }

    BigInt &operator+=(const BigInt &x) {
        for (int i = 0; i < LEN; i++) {
            a[i] += x.a[i];
            if (a[i] >= 10) {
                a[i + 1] += 1;
                a[i] -= 10;
            }
        }
        return *this;
    }
};