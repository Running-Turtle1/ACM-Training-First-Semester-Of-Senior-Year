#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, m, k, w;
int h[N];

void solve(){
	cin >> n >> m >> k >> w;
	for(int i = 1; i <= w; i ++){
		cin >> h[i];
	}
	vector<vector<int> > a(n + 3, vector<int> (m + 3, 0));
	auto insert = [&] (int x1, int x2, int y1, int y2) {
		a[x1][y1] ++;
		a[x2 + 1][y2 + 1] ++;
		a[x1][y2 + 1] --;
		a[x2 + 1][y1] --;
	};
	for(int x1 = 1; x1 <= n; x1 ++){
		for(int y1 = 1; y1 <= m; y1 ++){
			int x2 = x1 + k - 1;
			int y2 = y1 + k - 1;
			if(x2 <= n && y2 <= m){
				insert(x1, x2, y1, y2);
			}
		}
	}
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		a[i][j] = a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1] + a[i][j]; 
        }
    }
    // for(int i = 1; i <= n; i ++){
    //     for(int j = 1; j <= m; j ++){
    //  		cout<<a[i][j]<<" \n"[j==m];       
    //     }
    // }
    vector<int> nums;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		nums.emplace_back(a[i][j]);       
        }
    }
    sort(nums.begin(), nums.end(), [](int a,int b){
    	return a > b;
    });
    int res = 0;
    // int now = n * m - 1;
    sort(h + 1, h + w + 1, [](int a, int b){
    	return a>b;
    });
    for(int i = 1; i <= w; i ++){
    	res += h[i] * nums[i-1];//nums[now --];
    	// cout<<i<< ' '<<h[i]<<' '<<nums[i-1]<<'\n';
    }
    cout << res << '\n';
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