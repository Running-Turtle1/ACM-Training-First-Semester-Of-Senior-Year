// 带权并查集+离散化
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

const int N=10005;
int n,m,cnt;
int p[N],d[N];
map<int,int> mp;

int get(int x){ //离散化
  if(mp.count(x)==0) mp[x]=++cnt;
  return mp[x];
}
int find(int x){
  if(p[x]==x) return x;
  int t=find(p[x]); //记录新根t
  d[x]=(d[x]+d[p[x]])%2;    //先更新x到新根t的距离
  return p[x]=t;    //再更新p[x]，路径压缩
}
int main(){
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m*2;i++)p[i]=i;
  int res=m;
  for(int i=1;i<=m;i++){
    int x,y; char op[7];
    scanf("%d%d%s",&x,&y,op);
    x=get(x-1), y=get(y);
    int px=find(x),py=find(y);
    if(op[0]=='o'){ //奇数个1
      //在同一颗树且有偶数个1
      if(px==py&&((d[x]-d[y])%2+2)%2==0){ 
        res=i-1; break;
      }
      if(px!=py){ //不在同一颗树
        p[px]=py; //px指向py
        d[px]=(d[y]+1-d[x]+2)%2; //x在y下一层
      }
    }
    else{ //偶数个1
      //在同一颗树且有奇数个1
      if(px==py&&((d[y]-d[x])%2+2)%2==1){
        res=i-1; break;
      }
      if(px!=py){ //不在同一颗树
        p[px]=py; //px指向py
        d[px]=(d[y]-d[x]+2)%2; //x,y在同一层
      }
    }
    for(int k=1;k<=m*2;k++)cout<<d[k]<<' '<<find(k)<<"\n\n"[k==2*m];
  }
  printf("%d\n",res);
}