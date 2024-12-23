#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, m;
int p[N], t[N]; // 两种人的前缀和
int mx[N]; // 擅长前缀和
int sp[N], st[N]; // 两种技巧的前缀和

int a[N], b[N];

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n + m + 1; i ++){
		cin >> a[i];
	}
	for(int i = 1; i <= n + m + 1; i ++){
		cin >> b[i];
	}
	for(int i = 1; i <= n + m + 1; i ++){
		p[i] = p[i - 1], t[i] = t[i - 1];
		if(a[i] > b[i]) p[i] ++;
		else t[i] ++;
		mx[i] = mx[i - 1] + max(a[i], b[i]);
		sp[i] = sp[i - 1] + a[i];
		st[i] = st[i - 1] + b[i];
    }
    for(int i = 1; i <= n + m + 1; i ++){
    	int p1; // 维护最先出现 n 个 p 人的位置
    	int p2; // 维护最先出现 m 个 t 人的位置
    	int l = 0, r = n + m + 1;
    	while(l < r){
    		int mid = l + r >> 1;
    		if(p[mid] - (mid >= i && a[i] > b[i]) >= n) r = mid;
    		else l = mid + 1;
    	}
    	p1 = l;
    	l = 0, r = n + m + 1;
    	while(l < r){
    		int mid = l + r >> 1;
    		if(t[mid] - (mid >= i && b[i] > a[i]) >= m) r = mid;
    		else l = mid + 1;
    	}
    	p2 = l;

    	// if(i == 1){
    	// 	cout<<"p: "<<p1<<' '<<p2<<'\n';
    	// }

    	int res = 0;

    	if(p1 < p2){ // 先出现了 n 个 p 人
    		// int lambda = p1 - n; // 选了的 m 人
    		// int remain = 
    		res += mx[p1]; // 选 mx 部分
    		res += st[n + m + 1] - st[p1];
    		if(i <= p1) res -= max(a[i], b[i]);
    		else res -= b[i];
    	}	
    	else{ // m 个 t 人
    		res += mx[p2]; // 选 mx 部分
    		res += sp[n + m + 1] - sp[p2];
    		// if(i==1)cout<<"res: "<<res<<'\n';
    		// if(i==2)cout<<"res: "<<res<<'\n';

    		if(i <= p2) res -= max(a[i], b[i]);
    		else res -= a[i];
    	}

    	cout << res << " \n"[i == n + m + 1];
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