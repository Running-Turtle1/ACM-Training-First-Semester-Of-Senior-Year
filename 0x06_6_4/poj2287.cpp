#include<iostream>
#include<cstring>
#include<set>
using namespace std;
#define int long long

int n, a[1100], b[1100];

int mx(multiset<int> &st){
	return *prev(st.end());
}

int mn(multiset<int> &st){
	return *st.begin();
}

void solve(int T){
	// cin >> n;
	n = T;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    for(int i = 1; i <= n; i ++){
    	cin >> b[i];
    }
    multiset<int> sa, sb;
    sa.insert(a + 1, a + n + 1);
    sb.insert(b + 1, b + n + 1);
    int res = 0;
    while(sa.size()){
    	if(mx(sa) > mx(sb)){ // a 的最大更大
    		sa.erase(prev(sa.end()));
    		sb.erase(prev(sb.end()));
    		res ++;
    	}
    	else if(mx(sa) == mx(sb)){
    		int vala = *sa.begin();
    		int valb = *sb.begin();
    		if(vala == valb){
    			// sa.erase(prev(sa.end()));
    			// sb.erase(prev(sb.end()));
    			if(vala < mx(sb)) res --;
    			sa.erase(sa.begin());
    			sb.erase(prev(sb.end()));
    			
    		}
    		else if(vala < valb){
    			if(vala < mx(sb)) res --;
    			sa.erase(sa.begin());
    			sb.erase(prev(sb.end()));
    			
    		}
    		else{ // amin 与 bmax
    			sa.erase(sa.begin());
    			sb.erase(sb.begin());
    			res ++;
    		}
    	}
    	else{
    		sa.erase(sa.begin());
    		sb.erase(prev(sb.end()));
    		res --;
    	}
    }
    cout << res * 200 << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	int T;
	while(cin >> T, T != 0){
		solve(T);
	}
	return 0;
}