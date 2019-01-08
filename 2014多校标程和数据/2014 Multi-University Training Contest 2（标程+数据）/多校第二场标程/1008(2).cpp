/*
Date: 2014/06/02 09:38:11 Monday
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
typedef __int64 ll;
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

const int N=222222,M=111111;
int l,n,t,f[N],sz[N],x,MXtot,MYtot,link[N],p;
ll m,lans,y;
struct zcc{ll x,y;}a[N];
char s[9];
map<pll,ll>pos;
set<pll>PX[N],PY[N];
map<ll,int>MX,MY;
int getf(int x){if(x==f[x])return x;return f[x]=getf(f[x]);}
void ins(int x){
    if(pos.find(mp(a[x].x,a[x].y))!=pos.end()){
        sz[pos[mp(a[x].x,a[x].y)]]++;f[x]=pos[mp(a[x].x,a[x].y)];return;
    }
    pos[mp(a[x].x,a[x].y)]=x;
    if(!MX[a[x].x])MX[a[x].x]=++MXtot;
    if(!MY[a[x].y])MY[a[x].y]=++MYtot;
    PX[MX[a[x].x]].insert(mp(a[x].y,x));
    PY[MY[a[x].y]].insert(mp(a[x].x,x));
}
int main()
{
    scanf("%d%I64d",&n,&m);
    rep(i,1,n)f[i]=i,sz[i]=1,link[i]=i;
    rep(i,1,n)scanf("%I64d%I64d",&a[i].x,&a[i].y),ins(i);
    int C;scanf("%d",&C);
    rep(_,1,C){
        fflush(stdout);
        scanf("%s",s);
        if(s[0]=='Q'){
            scanf("%d",&x);x^=lans;x=link[x];y=getf(x);lans=0;
            ll X=a[y].x,Y=a[y].y,XX=MX[X],YY=MY[Y];
            for(set<pll>::iterator it=PX[XX].begin();it!=PX[XX].end();++it)if(it->Y!=y){
                lans=(lans+(it->X-Y)%mod*((it->X-Y)%mod)%mod*sz[it->Y]%mod)%mod;
                pos.erase(mp(X,it->X));PY[MY[it->X]].erase(mp(X,it->Y));
                sz[y]+=sz[it->Y];f[getf(it->Y)]=y;
            }PX[XX].clear();PX[XX].insert(mp(Y,y));
            for(set<pll>::iterator it=PY[YY].begin();it!=PY[YY].end();++it)if(it->Y!=y){
                lans=(lans+(it->X-X)%mod*((it->X-X)%mod)%mod*sz[it->Y]%mod)%mod;
                pos.erase(mp(it->X,Y));PX[MX[it->X]].erase(mp(Y,it->Y));
                sz[y]+=sz[it->Y];f[getf(it->Y)]=y;
            }PY[YY].clear();PY[YY].insert(mp(X,y));
            printf("%d\n",lans);
        }else{
            scanf("%d%I64d",&x,&y);x^=lans;p=link[x];sz[getf(p)]--;
            ++n;link[x]=n;x=getf(p);
            a[n]=a[x];f[n]=n;sz[n]=1;
            pos.erase(mp(a[x].x,a[x].y));
            switch(s[0]){
                case 'U':a[n].x-=y;break;
                case 'D':a[n].x+=y;break;
                case 'L':a[n].y-=y;break;
                case 'R':a[n].y+=y;break;
            }ins(n);
        }
    }
    return 0;
}
