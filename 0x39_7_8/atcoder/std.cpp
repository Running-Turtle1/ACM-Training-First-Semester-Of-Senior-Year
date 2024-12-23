#include<bits/stdc++.h>

using namespace std;

vector<long long> pfact(long long x){
  vector<long long> res;
  for(long long i=2;i*i<=x;i++){
    while(x%i==0){
      res.push_back(i);
      x/=i;
    }
  }
  if(x>1){res.push_back(x);}
  return res;
}

long long safe_pow(long long a,long long b){
  __int128 res=1;
  for(long long i=0;i<b;i++){
    res*=a;
    if(res>1e18){return 2e18;}
  }
  return res;
}

int main(){
  long long n;
  cin >> n;
  long long res=0;
  for(long long b=2;b<60;b++){
    long long l=2,r=2e9;
    while(l<=r){
      long long t=(l+r)/2;
      if(safe_pow(t,b)>n){r=t-1;}
      else{l=t+1;}
    }
    // a = [2,r] satisfy a^b <= n
    vector<long long> pf=pfact(b);
    bool same=false;
    for(long long i=1;i<pf.size();i++){
      if(pf[i-1]==pf[i]){same=true; break;}
    }
    if(same){continue;}
    if(pf.size()%2){res+=(r-1);}
    else{res-=(r-1);}
  }
  res++; // count 1
  cout << res << "\n";
  return 0;
}
