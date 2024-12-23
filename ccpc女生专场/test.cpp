#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, k;

struct Pokeman{
    int h, a, b, c, d, e, w, s;
    Pokeman() {}
    Pokeman(int h, int a, int b, int c, int d, int e, int w, int s)
    : h(h), a(a), b(b), c(c), d(d), e(e), w(w), s(s) {}
};

deque<Pokeman> q[2];  // q[0]是小A的宝可梦队列，q[1]是小B的队列

void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        int h, a, b, c, d, e, w;
        cin >> h >> a >> b >> c >> d >> e >> w;
        q[0].push_back(Pokeman(h, a, b, c, d, e, w, 0));  // 小A的宝可梦
    }
    for (int i = 1; i <= m; i++) {
        int h, a, b, c, d, e, w;
        cin >> h >> a >> b >> c >> d >> e >> w;
        q[1].push_back(Pokeman(h, a, b, c, d, e, w, 0));  // 小B的宝可梦
    }

    int round = 0;  // 轮数

    while (round < 2 * k) {
        round++;
        int fs = (round & 1) ^ 1, sc = (round & 1);  // fs: 进攻方; sc: 防守方

        auto& attacker = q[fs].front();
        auto& defender = q[sc].front();

        // 计算物理攻击、魔法攻击和大招伤害
        int physDamage = max(attacker.a - defender.c, 0LL);
        int magicDamage = max(attacker.b - defender.d, 0LL);
        int ultDamage = (attacker.s >= attacker.e) ? attacker.w : -1e9;  // 大招

        int chosenDamage = max({physDamage, magicDamage, ultDamage});

        // 执行攻击
        if (chosenDamage == ultDamage) {
            attacker.s -= attacker.e;  // 大招消耗能量
        } else {
            attacker.s++;  // 普通攻击积累能量
        }
        defender.h -= chosenDamage;  // 防守方掉血

        // 判断防守方是否阵亡
        if (defender.h <= 0) {
            q[sc].pop_front();  // 移除阵亡的宝可梦
            if (q[sc].empty()) {  // 防守方没有宝可梦了
                cout << (fs == 0 ? "Alice" : "Bob") << '\n';
                return;
            }
        } else {
            defender.s++;  // 防守方增加能量
        }

        // 攻击方换到队伍末尾
        q[fs].push_back(q[fs].front());
        q[fs].pop_front();
    }

    cout << "Draw\n";  // 平局
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
