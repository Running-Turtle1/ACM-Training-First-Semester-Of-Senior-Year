// Luogu P2607 [ZJOI2008] 骑士
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=1e6+10;
typedef long long LL;
int n;
struct edge{int v,ne;}e[N<<1];
int h[N],w[N],idx=1;
int r1,r2,vis[N],be[N<<1];
LL f[N][2],sum;

void add(int a,int b){
  e[++idx]={b,h[a]};h[a]=idx;
}
bool find(int u,int ine){
    vis[u]=true;
    for(int i=h[u];~i;i=e[i].ne){
      if(i==(ine^1))continue;
        int v=e[i].v;
        if(!vis[v]){//v尚未访问
            if(find(v,i)) return 1;
        } else{//v已访问
      r1=u,r2=v,be[i]=1,be[i^1]=1;
      return 1;
        }
    }
    return 0;
}
LL dfs(int u,int ine){//树上DP
  vis[u]=true;f[u][0]=0;f[u][1]=w[u];
  for(int i=h[u];~i;i=e[i].ne){
    if(i==(ine^1)||be[i])continue;
    int v=e[i].v;
    dfs(v,i);
    f[u][0]+=max(f[v][0],f[v][1]);
    f[u][1]+=f[v][0];
  }
  return f[u][0];
}
int main(){
  memset(h,-1,sizeof h);
  scanf("%d",&n);
  for(int v=1,u;v<=n;v++){
    scanf("%d%d",&w[v],&u);
    add(u,v);add(v,u);
  }
  for(int i=1;i<=n;i++){
    if(!vis[i]){
      r1=r2=0;
      find(i,0);
      if(r1){
        LL res1=dfs(r1,0);
        LL res2=dfs(r2,0);
        sum+=max(res1,res2);
      }
    }
  }
  printf("%lld",sum);
  return 0;
}