#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, k;

int const N = 1e5 + 10;

struct Pokeman{
	int h, a, b, c, d, e, w, s;
	// int pro, s;
	Pokeman() {}
	Pokeman(int h, int a, int b, int c, int d, int e, int w, int s)
	 : h(h), a(a), b(b), c(c), d(d), e(e), w(w), s(s) {}
	 // bool operator < (const Pokeman & T) const {
	 // 	return pro > T.pro;
	 // }
};//pokeman[N][2];

// int idx[2]; // 待用优先级

int Round = 1; // 即将进行的回合

// priority_queue<Pokeman> q[2]; // 默认大根堆
deque<Pokeman> q[2];

void solve(){
	cin >> n >> m >> k;
	// idx[0] = idx[1] = 1;
	Pokeman pet[2];
	for(int i = 1; i <= n; i ++){
		int h, a, b, c, d, e, w;
		cin >> h >> a >> b >> c >> d >> e >> w;
		// pokeman[i][0] = Pokeman(h, a, b, c, d, e, w, 0);
		// pokeman[i][0] = Pokeman(h, a, b, c, d, e, w, (idx[0] ++), 0);
		if(i != 1){
			 q[0].push_back(Pokeman(h, a, b, c, d, e, w, 0));
			 // q[0].push_back(pokeman[i][0]);
		}
		else pet[0] = Pokeman(h, a, b, c, d, e, w, 0);
    }
    for(int i = 1; i <= n; i ++){
		int h, a, b, c, d, e, w;
		cin >> h >> a >> b >> c >> d >> e >> w;
		// pokeman[i][1] = Pokeman(h, a, b, c, d, e, w, 0);
		if(i != 1){
			q[1].push_back(Pokeman(h, a, b, c, d, e, w, 0));
			 // q[0].push_back(pokeman[i][0]);
		}
		else pet[1] = Pokeman(h, a, b, c, d, e, w, 0);
    }
    
    // c[0] = pokeman[0][1], c[1] = pokeman[1][1];
    while(true){
    	if(Round == k + 1){
    		cout << "Draw\n";
    		return ;
    	}

    	int fs = (Round & 1) ^ 1, sc = (Round & 1);
    	auto &[h1, a1, b1, c1, d1, e1, w1, s1] = pet[fs];
    	auto &[h2, a2, b2, c2, d2, e2, w2, s2] = pet[sc];
    	int atk1 = max(max(a1 - c2, 0LL), max(b1 - d2, 0LL));
    	int atk2 = (s1 >= e1) ? w1 : -1e9;
    	if(atk1 >= atk2){
    		// 执行进攻方逻辑
    		s1 ++; // 获得能量
    		// pro1 = idx[(Round & 1) ^ 1] ++;
    		// q[(Round & 1) ^ 1].push(c[0]);
    		// c[0] = q[(Round & 1) ^ 1].top();
    	}
    	else{ // 释放大招
    		s1 -= e1;
    		// pro1 = idx[(Round & 1) ^ 1] ++;
    		// q[(Round & 1) ^ 1].push(c[0]);
    		// c[0] = q[(Round & 1) ^ 1].top();
    	}
    	q[fs].push_back(pet[fs]); // 归队
		pet[fs] = q[fs].front();
		q[fs].pop_front();

    	// 执行防守方逻辑
		h2 -= max(atk1, atk2);
		if(h2 <= 0){ // 死了,
			if(q[sc].size() == 0){ // 游戏结束
				if(fs == 0) cout << "A";
				else cout << "B";
				exit(0);
			}
			// if(q[(Round & 1)].size() == 0) {
			// 	if((Round & 1)){ // A 进攻
			// 		cout << "A\n";
			// 	}
			// 	else{
			// 		cout << "B\n";
			// 	}
			// 	exit(0);
			// }
			// c[(Round & 1)] = q[(Round & 1)].top(); q[(Round & 1)].pop();
			pet[sc] = q[sc].front();
			q[sc].pop_front();
		}
		else{
			s2 ++; // 挨揍收集能量

		}

		q[sc].push_back(pet[sc]); // 归队
		pet[sc] = q[sc].front();
		q[sc].pop_front();
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
