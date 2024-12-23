#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n;
int a[N], sa[N];
int b[N], sb[N];
int c[N], sc[N];

int ask(int l, int r, int *s){
	if(l > r) return 0;
	return s[r] - s[l - 1];
}

void solve(){
	int tot = 0;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		sa[i] = sa[i - 1] + a[i];
		tot += a[i];
    }
    for(int i = 1; i <= n; i ++){
		cin >> b[i];
		sb[i] = sb[i - 1] + b[i];
    }
    for(int i = 1; i <= n; i ++){
		cin >> c[i];
		sc[i] = sc[i - 1] + c[i];
    }
    int target = (tot + 2) / 3;
    // cout << ask(2, 4, sa) << '\n';
    // cout << target << '\n';
    // 枚举 a 的起点选择 
    for(int la = 1; la <= n; la ++){
    	if(ask(la, n, sa) < target) break;
    	int l = la, r = n;
    	while(l < r){
    		int mid = l + r >> 1;
    		if(ask(la, mid, sa) >= target) r = mid;
    		else l = mid + 1;
    	}
    	int ra = l;
    	// if(la==1){
    	// 	cout<<la<<' '<<ra<<'\n';
    	// }
    	// [la, ra]
    	int fg1, fg2, fg3, fg4;
    	fg1 = ask(1, la - 1, sb) >= target;
    	fg2 = ask(ra + 1, n, sb) >= target;
    	fg3 = ask(1, la - 1, sc) >= target;
    	fg4 = ask(ra + 1, n, sc) >= target;
    	// if(la == 1){
    	// 	cout << fg1 << ' ' << fg2 << ' ' << fg3 << ' ' << fg4 << '\n';
    	// }
    	if(fg1 && fg4){
    		cout << la << ' ' << ra << ' ';
    		cout << 1 << ' ' << la - 1 << ' ';
    		cout << ra + 1 << ' ' << n << '\n';
    		return ;
    	}
    	if(fg2 && fg3){
    		cout << la << ' ' << ra << ' ';
    		cout << ra + 1 << ' ' << n << ' ';
    		cout << 1 << ' ' << la - 1 << '\n';
    		return ;
    	}
    	if(!fg3 && !fg4) continue;
    	if(!fg1 && !fg2) continue;
    	if(fg1 && fg3){ // 看看左侧是否合法
    		l = 1, r = la - 1;
    		while(l < r){
    			int mid = l + r >> 1;
    			if(ask(1, mid, sb) >= target) r = mid;
    			else l = mid + 1;
    		}
    		if(ask(l + 1, la - 1, sc) >= target){
    			cout << la << ' ' << ra << ' ';
    			cout << 1 << ' ' << l << ' ';
    			cout << l + 1 << ' ' << la - 1 << '\n';
    			return ;
    		}
    		l = 1, r = la - 1;
    		while(l < r){
    			int mid = l + r + 1 >> 1;
    			if(ask(mid, la - 1, sb) >= target) l = mid;
    			else r = mid - 1;
    		}
    		if(ask(1, l - 1, sc) >= target){
    			cout << la << ' ' << ra << ' ';
    			cout << l << ' ' << la - 1 << ' ';
    			cout << 1 << ' ' << l - 1 << '\n';
    			return ;
    		}
    	}
    	if(fg2 && fg4){ // 看看右侧是否合法
    		// if(la==1)cout<<"in\n";
    		l = ra + 1, r = n;
    		while(l < r){
    			int mid = l + r >> 1;
    			if(ask(ra + 1, mid, sb) >= target) r = mid;
    			else l = mid + 1;
    		}
    		if(ask(l + 1, n, sc) >= target){
    			cout << la << ' ' << ra << ' ';
    			cout << ra + 1 << ' ' << l << ' ';
    			cout << l + 1 << ' ' << n << '\n';
    			return ;
    		}
    		l = ra + 1, r = n;
    		while(l < r){
    			int mid = l + r + 1 >> 1;
    			if(ask(mid, n, sb) >= target) l = mid;
    			else r = mid - 1;
    		}
    		if(ask(ra + 1, l - 1, sc) >= target){
    			cout << la << ' ' << ra << ' ';
    			cout << l << ' ' << n << ' ';
    			cout << ra + 1 << ' ' << l - 1 << '\n';
    			return ;
    		}
    	}
    }
    cout << "-1\n";
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