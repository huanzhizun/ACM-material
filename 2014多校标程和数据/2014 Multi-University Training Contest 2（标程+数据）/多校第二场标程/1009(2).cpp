/*
Date: 2014/05/31 11:14:06 Saturday
Author: xllend3
*/
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<string>
#include<vector>
#include<queue>
#include<cmath>
#include<stack>
#include<map>
#include<set>
#define X first
#define Y second
#define mp make_pair
#define ph push
#define pb push_back
#define rep(i,a,n) for (int i = a; i <= n; ++i)
#define dep(i,a,n) for (int i = a; i >= n; --i)
#define re(b,a) for(a::iterator it=b.begin();it!=b.end();++it)
#define eps 1e-8
#define lowbit(x) (x&(-x))
#define pi 3.1415926535897
#define sqr(x) ((x)*(x))
#define MAX(a,b) a=max(a,b)
#define MIN(a,b) a=min(a,b)
#define SZ(x) ((int)(x).size())
#define CPY(a,b) memcpy(a,b,sizeof(a))
#define CLR(a) memset(a,0,sizeof(a))
#define POSIN(x,y) (1<=(x)&&(x)<=n&&1<=(y)&&(y)<=m)
#define all(x) (x).begin(),(x).end()
using namespace std;
typedef long long ll;
typedef double lf;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<lf,lf> pff;
typedef complex<double> CD;
const int inf=0x20202020;
const int mod=1000000007;
inline void read(int &x)
{
   char ch;bool f=0;int a=0;
   while(!((((ch=getchar())>='0')&&(ch<='9'))||(ch=='-')));
   if(ch!='-')a*=10,a+=ch-'0';else f=1;
   while(((ch=getchar())>='0')&&(ch<='9'))a*=10,a+=ch-'0';
   if(f)a=-a;x=a;
}
const int DX[]={1,0,-1,0},DY[]={0,1,0,-1};
ll powmod(ll a,ll b) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll powmod(ll a,ll b,ll mod) {ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
//*******************************************

const int N=111111,M=111;
int l,m,n,t,pt[N],pt2[N];
vector<int>ans[N];
struct zcc{int a[M][M];}Ans;
void mov(int *a,int n){
    int tmp=a[1];rep(i,1,n-1)a[i]=a[i+1];a[n]=tmp;
}
zcc work(int x){
    if(x==2){zcc a;a.a[1][1]=a.a[2][2]=1;a.a[2][1]=a.a[1][2]=2;return a;}
    if(x&1){
        zcc ans=work(x+1);
        rep(i,1,x)rep(j,2,x+1)if(ans.a[i][j]==x+1)ans.a[i][j]=0;
        return ans;
    }else{
        int n=x>>1;zcc ans=work(n);int v1[M],v2[M],cnt=0;
        if(n&1){
            rep(i,n+1,2*n)rep(j,1,n+1)ans.a[i][j]=ans.a[i-n][j]+n;
            rep(i,2,n+1){
                int v,tot=0;
                rep(j,1,n)if(!ans.a[j][i])v=j;
                ans.a[v][i]=v+n;ans.a[v+n][i]=v;
                v1[i-1]=v;v2[i-1]=v+n;
            }
            rep(i,1,n-1){
                mov(v2,n);
                rep(j,1,n)ans.a[v1[j]][i+n+1]=v2[j];
                rep(j,1,n)ans.a[v2[j]][i+n+1]=v1[j];
            }
        }else{
            rep(i,n+1,2*n)rep(j,1,n)ans.a[i][j]=ans.a[i-n][j]+n;
            rep(i,1,n)v1[i]=i,v2[i]=n+i;
            rep(i,1,n){
                mov(v2,n);
                rep(j,1,n)ans.a[v1[j]][i+n]=v2[j];
                rep(j,1,n)ans.a[v2[j]][i+n]=v1[j];
            }
        }return ans;
    }
}
int main()
{
    int _=0;
    while(scanf("%d%d",&n,&m)!=EOF){
        ++_;printf("Case #%d:\n",_);
        t=m;
        if(m==1){
            printf("%d\n",n-1);rep(i,1,n)printf("%d\n",i);
        }else if(m&1){
            if(n&1){
                rep(i,1,n)ans[i].clear();
                while(m>3){
                    rep(i,1,n)ans[i].pb(i),ans[i].pb(n-i+1);m-=2;
                }rep(i,1,n)ans[i].pb(i);
                rep(i,1,n)ans[i].pb((n/2+i-1)%n+1);
                rep(i,1,n)ans[i].pb((n+1)/2*3-ans[i][t-3]-ans[i][t-2]);
                puts("0");
            }else{
                rep(i,1,n)ans[i].clear();
                while(m>3){
                    rep(i,1,n)ans[i].pb(i),ans[i].pb(n-i+1);m-=2;
                }rep(i,1,n)ans[i].pb(i);
                rep(i,1,n)ans[i].pb((n/2+i-1)%n+1);
                rep(i,1,n/2)ans[i].pb(n/2*3+2-ans[i][t-3]-ans[i][t-2]);
                rep(i,1,n/2)ans[i+n/2].pb(n/2*3+2-ans[i][t-3]-ans[i][t-2]-1);
                puts("1");
            }rep(i,1,n){rep(j,0,SZ(ans[i])-2)printf("%d ",ans[i][j]);printf("%d\n",ans[i][SZ(ans[i])-1]);}
        }else{
            rep(i,1,n)ans[i].clear();
            rep(i,1,n)rep(j,1,m/2)ans[i].pb(i),ans[i].pb(n-i+1);
            puts("0");
            rep(i,1,n){rep(j,0,SZ(ans[i])-2)printf("%d ",ans[i][j]);printf("%d\n",ans[i][SZ(ans[i])-1]);}
        }
        if(n&1){puts("No");continue;}
        puts("Yes");if(n>100)continue;
        Ans=work(n);
        rep(i,1,n)ans[i].clear(),pt[i]=i;
        rep(i,1,n){
            rep(j,1,n)ans[pt[j]].pb(Ans.a[j][i]);
            rep(j,1,n)pt2[Ans.a[j][i]]=pt[j];
            CPY(pt,pt2);
        }
        rep(i,1,n){rep(j,0,SZ(ans[i])-2)printf("%d ",ans[i][j]);printf("%d\n",ans[i][SZ(ans[i])-1]);}
    }
    return 0;
}
