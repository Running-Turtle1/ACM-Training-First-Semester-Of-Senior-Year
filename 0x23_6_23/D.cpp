//#define _GLIBCXX_DEBUG
#include<atcoder/all>
#include<bits/stdc++.h>
using namespace std;
using namespace atcoder;
#define rep(i,n) for(ll i=0;i<(n);i++)
#define nrep(i,a,b) for(ll i=a;i<(b);i++)
#define ALL(a) a.begin(),a.end()
#define ll long long
#define ull unsigned long long
#define ld long double
#define pint pair<int,int>
#define pll pair<ll,ll>
vector<int> dx = {1,0,-1,0};
vector<int> dy = {0,1,0,-1};
ll INF = 1LL<<62;
template<class T>
void chmax(T& a,T b){if(a < b) a = b;}
template<class T>
void chmin(T& a,T b){if(a > b) a = b;}
bool inr(ll x,ll a,ll b){return a<=x&&x<b;}
using mint = modint998244353;
ll N,K;
bool kaibun(string s){
  ll a = s.size();
  bool ans = true;
  rep(i,a/2) if(s[i]!=s[a-i-1]) ans = false;
  return ans; 
}
bool kaibun(int a){
  string s;
  rep(i,K){
    if((a>>i)&1) s.push_back('A');
    else s.push_back('B');
  }
  return kaibun(s);
}
int to_bit(string s){
  ll a = s.size();
  int ans = 0;
  rep(i,a) if(s[i] == 'A') ans += 1<<i;
  return ans;
}

int main(){
  
  cin >> N >> K;
  string S;
  cin >> S;
  vector<vector<mint>> dp(N+1,vector<mint>(1<<(K-1)));
  vector<int> start;
  rep(i,1<<(K-1)){
    bool ok = true;
    rep(j,K-1){
      if(S[j] == '?') continue;
      if((S[j] == 'A') != ((i>>j)&1)) ok = false;
    }
    if(ok) start.push_back(i);
  }
  for(int a : start) dp[K-1][a] = 1;
  nrep(i,K-1,N){
    rep(j,1<<(K-1)){
      if(S[i]=='?'){
        S[i] = 'A';
        int nj = j>>1;
        if(S[i]=='A') nj += 1<<(K-2);
        if(!kaibun(j+(S[i]=='A' ? 1 : 0)*(1<<(K-1)))) dp[i+1][nj] += dp[i][j];
        S[i] = 'B';
        nj = j>>1;
        if(S[i]=='A') nj += 1<<(K-2);
        if(!kaibun(j+(S[i]=='A' ? 1 : 0)*(1<<(K-1)))) dp[i+1][nj] += dp[i][j];
        S[i] = '?';
      }
      else{
        int nj = j>>1;
        if(S[i]=='A') nj += 1<<(K-2);
        ll n = j+(S[i]=='A' ? 1 : 0)*(1<<(K-1));
        if(!kaibun(n)) dp[i+1][nj] += dp[i][j];
      }
    }
  }
  mint ans = 0;
  rep(i,1<<(K-1)) ans += dp[N][i];
  cout << ans.val() << endl;


}