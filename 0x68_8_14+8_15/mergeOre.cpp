#include<bits/stdc++.h>
using namespace std;
#define int long long

int v[12];
double d[3100]; // 重量 i 的最大净含量
int a[3100], b[3100];
int st[3100];
int n, m;

int get(double val) {
	val *= 10;
	return ceil(val);
}

void dijkstra(){
	for(int i = 1; i <= m; i ++){
		st[i] = 0; // 没考虑过这个这个质量
	}
	// 找一个可以考虑的质量
	// 当前质量最小
	int mnPos = -1;
	for(int i = 1; i <= m; i ++){
		if(fabs(d[i] + 1e16) < 1e-3){ // 可以考虑
			continue ;
		} 
		mnPos = i;
		break;
	}

	// 取出质量最小
	priority_queue<pair<int, double>, vector<pair<int, double>>, greater<pair<int, double>> > heap;
	heap.push({mnPos, d[mnPos]});

	while(heap.size()){
		auto const [weight, hl] = heap.top(); // 堆顶
		// cout << weight << '\n.;
		heap.pop();

		if(st[weight]) continue ;

		st[weight] = 1;
		for(int w = 1; w <= m; w ++){
			if(fabs(d[w] + 1e16) < 1e-3) { // 不存在该重量
				continue ;
			}
			// cout << "Find: " << w << '\n';
			int nw = weight + w;
			double nhl = (weight * hl + w * d[w]) / (1.0 * nw);
			if(nw <= m && (fabs(d[nw] + 1e16) < 1e-3 || get(nhl) > get(d[nw]))){
				d[nw] = nhl;
				heap.push({nw, d[nw]});
			}
		}
	}
}
// 
int dp[3100]; // 考虑到重量 i , <= j 的完全背包的最大取得量
void solve(){
	for(int i = 1; i <= 10; i ++){
		cin >> v[i];
	}
	cin >> n >> m;
	for(int i = 1; i <= m; i ++){
		d[i] = -1e16; // 初始化为 \-infty
	}
	for(int i = 1; i <= n; i ++){
		cin >> a[i] >> b[i];
		d[a[i]] = max(d[a[i]], 1.0 * b[i] / a[i]);
		// cout << a[i] << ' ' << b[i] << '\n';
    }
    dijkstra();


    // for(int i = 1; i <= 10; i ++){
    // 	cout << "weight: " << i << '\n';
    // 	cout << "hanlaing: " << d[i] << '\n';
    // }

	for(int j = 0; j <= m; j ++){
		dp[j] = 0;
	}

    for(int i = 1; i <= m; i ++){ // 考虑所有重量 i
    	if(fabs(d[i] + 1e16) < 1e-3) continue; // 不可选择
    	for(int j = i; j <= m; j ++){
    		// 体积是 i, 价值是 v[i]
    		dp[j] = max(dp[j], dp[j - i] + i * v[get(d[i])]);
    	}
    }

    cout << dp[m] << '\n';
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