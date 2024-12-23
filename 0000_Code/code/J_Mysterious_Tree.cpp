#include<bits/stdc++.h>
using namespace std;

int n;

int ask(int x, int y){
	cout << "? " << x << ' ' << y << endl;
	int res;
	cin >> res;
	return res;
}

void sol(int res){
	cout << "! " << res << endl;
}

void solve(){
	int s = 0, x, y;
	cin >> n;
	for(int i = 1; i <= n - 1; i += 2){
		int t = ask(i, i + 1);
		if(t == 1){
			s ++;
			x = i, y = i + 1;
		}
	}
	if(s >= 2) sol(1);
	else if(s == 0){
		if(n % 2 == 0){ // ou shu
			sol(1);
			return ;
		}
		// jishu : lian ; ju hua
		int tmp = 0;
		for(int i = 1; i <= 3; i ++){
			tmp += ask(n, i);
		}
		if(tmp == 3) sol(2);
		else sol(1);
	}
	else{
		int fs = -1, sc;
		for(int i = 1; i <= n; i ++){
			if(i != x && i != y){
				if(fs == -1) fs = i;
				else{
					sc = i;
					break;
				}
			}
		}
		int t1 = ask(x, fs);
		int t2 = ask(y, fs);
		if(t1 == 0 && t2 == 0) sol(1);
		else{
			int t = 0;
			if(t1) {
				t = ask(x, sc);
			}
			else{
				t = ask(y, sc);
			}
			if(t) sol(2);
			else sol(1);
		}
	} 
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	int T;
	cin >> T;
	while(T --){
		solve();
	}
	
	return 0;
}