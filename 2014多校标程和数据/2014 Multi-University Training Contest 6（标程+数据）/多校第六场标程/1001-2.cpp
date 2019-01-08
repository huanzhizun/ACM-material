#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>
#define DBLE 1e-8
#define PI 3.1415926535898
#define INF 1000000000
#define MAXN (1<<10)
using namespace std;
const int MAXM = 10010, MAXK = 1010;
bool visit[MAXM];
int son[MAXM],tn[MAXM],ni[MAXM],nj[MAXM];
long long maxi[MAXK];
long long num[20][MAXK];
int dp[2][MAXN], top;
double init(int n)
{
    top=1;
    double sum=1;
    for(int i=0,j,now;i<n;++i)
        if(!visit[i])
        {
            for(j=0,now=i;now!=-1;now=son[now],++j)
                num[top][j]=tn[now],++ni[j],maxi[j]+=1<<(top-1);
            sum*=(j+1);
            nj[top]=j;
            ++top;
        }
    return sum-1;
}
double cal(int i,int j)
{
    double sum=0,n=1;
    int cnt=0;
    for(int k=1;k<=10;++k,j>>=1)
    {
        if(j&1)
            sum+=num[k][i],n*=(nj[k]-i),++cnt;
        else    n*=min(nj[k],i)+1;
    }
    return sum*((cnt>1?cnt:0)+ni[i])/ni[i]*n;
}
int main()
{
    //freopen("data.in", "r", stdin);
    //freopen("/home/caesar11/out", "w", stdout);
    int n,m,a,b;
    double sum=0, sum2;
    int ncase;
    scanf("%d", &ncase);
    while(ncase--)
    {
        scanf("%d%d",&n,&m);
        memset(son,-1,sizeof(son));
        memset(num,0,sizeof(num));
        memset(visit,0,sizeof(visit));
        memset(ni,0,sizeof(ni));
        memset(maxi,0,sizeof(maxi));
        memset(nj,0,sizeof(nj));
        for(int i=0;i<n;++i)
            scanf("%d",&tn[i]);
        for(int i=0;i<m;++i)
            scanf("%d%d",&a,&b),son[a]=b,visit[b]=1;
        sum2=init(n);
        sum=0;
        for(int i=0;ni[i];++i)
            for(int j=maxi[i];j>0;j=(j-1)&maxi[i])
                sum+=cal(i,j);
        //printf("%.3f %.3f\n",sum,sum2);
        printf("%.3f\n",sum/sum2);
    }
    return 0;
}
