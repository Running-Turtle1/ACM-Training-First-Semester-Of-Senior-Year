#include<bits/stdc++.h>
using namespace std;
#define int long long

bool isPrime(int x){
	for(int i = 2; i <= x / i; i ++){
		if(x % i == 0) return false;
	}
	return true;
}
int n, k;
int cnt = 0;
vector<int> pm; // [2, 60] 内的质数
void init(){
	int cnt = 0;
	for(int i = 2; i < 60; i ++){
		if(isPrime(i)){
			pm.push_back(i);
		}
    }
}

int Pow(int a, int b){
	int res = 1;
	for(int i = 1; i <= b; i ++){
		if(res >= (n + 1 + a - 1) / a){
			return n + 10;
		}
		res = res * a;
	}
	return res;
}

// 计算 [2, n] 中 a^p 的 a 的取值个数
// 其中 p >= 2
int cal(int p){
	if(Pow(2LL, p) > n) return 0;
	int l = 2, r = 1e9;
	while(l < r){
		int mid = l + r + 1 >> 1;
		if(Pow(mid, p) <= n) l = mid;
		else r = mid - 1;
	}
	// [2, l] 都可以取到
	return l - 1;
}

void solve(){
	cin >> n >> k;
	if(k == 1){
		cout << n << '\n';
		return ;
	}

	int res = 1; // add the case 1
	init(); // 预处理质数, cnt, pm
	cnt = pm.size(); 

	if(k == 3){
		// vector<int> v(pm.begin() + 1, pm.end());
		// swap(v, pm);
		unordered_set<int> s;
		for(int i = 3; i < 60; i ++){ // b
			for(int j = 1; ; j ++){
				if(Pow(j, i) > n) break;
				s.insert(Pow(j, i));
			}
		}
		cout << s.size() << '\n';
		return ;
	}
	// cnt --;
	// for(int i = 0; i < cnt; i ++){
	// 	cout << i << ' ' << pm[i] << '\n';
	// }

	for(int i = 1; i < 1 << cnt; i ++){
		int s = 0;
		int p = 1;
		bool fg = false; // 防止 p 累乘起来太大
		for(int j = 0; j < cnt; j ++){
			if(i >> j & 1){
				s ++;
				if(p >= (n + 1 + pm[j] - 1) / pm[j]){
					fg = true;
					break;
				}
				p *= pm[j];
			}
		}
		if(fg) continue ; 
		if(cal(p)){
			cout << "Prime: ";
			// cout << ((s & 1) ? "")
			cout << p << ' ' << cal(p) << '\n';
		}
		if(s & 1) res += cal(p);
		else res -= cal(p);
	}
	cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
