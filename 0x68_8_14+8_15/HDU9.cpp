#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, a[N], b[N];
int has[N]; // 牌堆里面是否有某张牌
int paidui[N], cnt; // 牌堆

struct card{
	set<int> two;
	set<int> oneown;
	set<int> onehehas;
};

void solve(){
	map<int, int> ca, cb;
	cnt = 0;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		has[i] = 0;
		ca[a[i]] ++;
    }
    for(int i = 1; i <= n; i ++){
    	cin >> b[i];
    	cb[b[i]] ++;
    }

    card A, B;
    for(auto &[x, y] : ca){
    	if(y == 2){
    		A.two.insert(x);
    	}
    	else if(y == 1){
    		A.onehehas.insert(x);
    	}
    }
    for(auto &[x, y] : cb){
    	if(y == 2){
    		B.two.insert(x);
    	}
    	else if(y == 1){
    		B.onehehas.insert(x);
    	}
    }

    auto add = [&] (int x) -> int {
    	int s = 0;
    	if(has[x] == false) {
    		has[x] = true;
    		paidui[++ cnt] = x;
    	}
    	else{ 
    		while(cnt >= 1 && paidui[cnt] != x){
    			cnt --;
    			s ++;
    		}
    		cnt --;
    		s += 2;
    	}
    	return s;
    };

    auto givecard = [&] (card &c, card &opponent) -> int {
    	if(c.two.size()){
    		int x = *c.two.begin();
    		c.two.erase(x);
    		c.oneown.insert(x);
    		return x;
    	}
    	if(c.oneown.size()){
    		int x = *c.oneown.begin();
    		c.oneown.erase(x);
    		return x;
    	}
    	int x = *c.onehehas.begin(); // 对面有的
    	c.onehehas.erase(x);
    	opponent.onehehas.erase(x);
    	opponent.oneown.insert(x);
    	return x;
    };

    int s1 = 0, s2 = 0;
    for(int i = 1; i <= 2 * n; i ++){
    	if(i & 1){ // 先手
    		int x = givecard(A, B);
    		s1 += add(x);
    	}	
    	else{ // 后手
    		int x = givecard(B, A);
    		s2 += add(x);
    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}