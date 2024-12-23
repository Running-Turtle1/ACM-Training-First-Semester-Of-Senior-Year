#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, k;

struct Pokeman{
	int h, a, b, c, d, e, w, s;
	// int pro, s;
	Pokeman() {}
	Pokeman(int h, int a, int b, int c, int d, int e, int w, int s)
	 : h(h), a(a), b(b), c(c), d(d), e(e), w(w), s(s) {}
};

int Round = 1; // 即将进行的回合
deque<Pokeman> q[2];

void solve(){
	cin >> n >> m >> k;
	Pokeman pet[2]; // 初始宝可梦
	for(int i = 1; i <= n; i ++){
		int h, a, b, c, d, e, w;
		cin >> h >> a >> b >> c >> d >> e >> w;
		if(i != 1) q[0].push_back(Pokeman(h, a, b, c, d, e, w, 0)); // 待出战
		else pet[0] = Pokeman(h, a, b, c, d, e, w, 0);
    }
    for(int i = 1; i <= m; i ++){
		int h, a, b, c, d, e, w;
		cin >> h >> a >> b >> c >> d >> e >> w;
		if(i != 1) q[1].push_back(Pokeman(h, a, b, c, d, e, w, 0)); // 待出战
		else pet[1] = Pokeman(h, a, b, c, d, e, w, 0);
    }

    while(true){
    	if((Round) == 2 * k + 1){ // 执行到第 2 * k + 1 轮游戏, 约定平局, 进行过了 K 轮比试
    		cout << "Draw\n";
    		return ;
    	}

    	int fs = (Round & 1) ^ 1, sc = (Round & 1); // fs : 进攻方 ; sc : 防守方
    	auto &[h1, a1, b1, c1, d1, e1, w1, s1] = pet[fs];
    	auto &[h2, a2, b2, c2, d2, e2, w2, s2] = pet[sc];
    	int atk1 = max(max(a1 - c2, 0LL), max(b1 - d2, 0LL)); // 普通攻击
    	int atk2 = (s1 >= e1) ? w1 : -1e9; // 释放大招

    	// 执行进攻方逻辑
    	if(atk1 >= atk2){
    		s1 ++; // 获得能量
    		h2 -= atk1;
    	}
    	else{ // 释放大招
    		s1 -= e1;
    		h2 -= atk2;
    	}
    	q[fs].push_back(pet[fs]); // 归队
		pet[fs] = q[fs].front(), q[fs].pop_front(); // 新宝可梦

    	// 执行防守方逻辑
		if(h2 <= 0){ // 阵亡逻辑
			if(q[sc].size() == 0){ // 无法出战, 游戏结束
				cout << ((fs == 0) ? "Alice" : "Bob") << '\n';
				exit(0); // 退出游戏
			}
			pet[sc] = q[sc].front(), q[sc].pop_front(); // 切换宝可梦	
		}

		Round ++;
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
