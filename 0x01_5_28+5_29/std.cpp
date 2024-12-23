#include<bits/stdc++.h>
using namespace std;
#define int long long

int f[4100][4100],n,k;
int cali(int i,int j){return i+j-1;};
int calj(int i,int j){return n+j-i;};
int cal(int i, int j){
	return f[i][j]-(i>=k?f[i-k][j]:0)
	-(j>=k?f[i][j-k]:0)+(i>=k&&j>=k?f[i-k][j-k]:0);
}

void solve(){
	cin>>n>>k;
	int w,nn=n;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            cin>>w;
            f[cali(i,j)][calj(i,j)]=w;
        }
    }
    n=n*2-1,k=k*2-1;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            f[i][j]+=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
        }
    }
    int ans=0;
    int typ=nn&1;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            if((i&1)^(j&1)^typ){
            	ans=max(ans,cal(i,j));
            }
        }
    }
    cout<<ans;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}