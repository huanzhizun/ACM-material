#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#define __int64 long long
using namespace std;
struct node
{
	int fa,cnt;
}f[200010];
struct point1
{
	int fa;
	LL x,y;
	bool operator <(const point1&A) const
	{
		if (A.x==x) return A.y>y;
		return A.x>x;
	}
};
point1 make1(LL x,LL y,int fa)
{
	point1 ans;ans.x=x;ans.y=y;ans.fa=fa;return ans;
}
struct point2
{
	int fa;
	LL x,y;
	bool operator <(const point2&A) const
	{
		if (A.y==y) return A.x>x;
		return A.y>y;
	}
};
point2 make2(LL x,LL y,int fa)
{
	point2 ans;ans.x=x;ans.y=y;ans.fa=fa;return ans;
}
LL m,y;
node find(int x)
{
	if (f[x].fa==x) return f[x];
	node tmp=find(f[x].fa);
	f[x].fa=tmp.fa;
	f[x].cnt=tmp.cnt;
	return f[x];
}
void Union(int x,int y)
{
	int u=find(x).fa,v=find(y).fa;
	int tmp=f[v].cnt;
	f[u].cnt+=tmp;
	f[v].fa=u;
}
int n,Q,x,P=1000000007;
char s[2];
struct point
{
	LL x,y;
	int fa;
}p[200010];
int New[100010],te;
set<point1> X;
set<point2> Y;
void read(int &x)
{
	char ch=getchar();int mark=1;for(;ch!='-'&&(ch<'0'||ch>'9');ch=getchar());if (ch=='-') mark=-1,ch=getchar();
	for(x=0;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-48;x*=mark;
}
void Add(LL x,LL y,int fa)
{
	f[fa].fa=fa;f[fa].cnt=1;
	set<point1>:: iterator it=X.lower_bound(make1(x,y,fa));
	if (it->x==x&&it->y==y) Union(it->fa,fa);
	else X.insert(make1(x,y,fa));
	set<point2>:: iterator It=Y.lower_bound(make2(x,y,fa));
	if (It->x==x&&It->y==y);
	else Y.insert(make2(x,y,fa));
}
inline int sqr(LL x){x%=P;return x*x%P;}
inline int dis(LL x1,LL y1,LL x2,LL y2)
{
	return (sqr(x1-x2)+sqr(y1-y2))%P;
}
int Sm_x(int x)
{
	set<point1>::iterator it,L,R,tmp;
	int t=find(p[x].fa).fa;
	it=L=R=X.lower_bound(make1(p[t].x,p[t].y,0));
	for(;L->x==p[t].x;--L);++L;
	for(;R->x==p[t].x;++R);
	int ans=0;
	for(;L!=R;)
	{
		tmp=L;
		if (it!=L)
		{
			(ans+=(LL)find(L->fa).cnt*dis(L->x,L->y,it->x,it->y)%P)%=P;
			Union(it->fa,L->fa);
			L++;
			X.erase(tmp);
			Y.erase(make2(tmp->x,tmp->y,tmp->fa));
		}
		else L++;
	}
	return ans;
}
int Sm_y(int x)
{
	set<point2>::iterator it,L,R,tmp;
	int t=find(p[x].fa).fa;
	it=L=R=Y.lower_bound(make2(p[t].x,p[t].y,0));
	for(;L->y==p[t].y;--L);++L;
	for(;R->y==p[t].y;++R);
	int ans=0;
	for(;L!=R;)
	{
		tmp=L;
		if (it!=L)
		{
			(ans+=(LL)find(L->fa).cnt*dis(L->x,L->y,it->x,it->y)%P)%=P;
			Union(it->fa,L->fa);
			L++;
			Y.erase(tmp);
			X.erase(make1(tmp->x,tmp->y,tmp->fa));
		}
		else L++;
	}
	return ans;
}
int main()
{
	//freopen("zcc_loves_march.in","r",stdin);
	//freopen("zcc_loves_march.out","w",stdout);
while(scanf("%d%I64d",&n,&m)!=EOF)
{
	printf("Case #%d:\n",++te);
	X.clear();Y.clear();
	X.insert(make1(-1,0,0));
	X.insert(make1(m+1,0,0));
	Y.insert(make2(0,-1,0));
	Y.insert(make2(0,m+1,0));
	for(int i=1;i<=n;i++)
	{
		scanf("%I64d%I64d",&p[i].x,&p[i].y);p[i].fa=i;
		Add(p[i].x,p[i].y,p[i].fa);
		New[i]=i;
	}
	int pre=0;
	read(Q);
	for(int i=1;i<=Q;i++)
	{
		scanf("%s",s);
		if (s[0]=='Q')
		{
			scanf("%d",&x);
			x^=pre;
			x=New[x];
			pre=(Sm_x(x)+Sm_y(x))%P;
			printf("%d\n",pre);
			fflush(stdout);
		}
		else 
		{
			scanf("%d%I64d",&x,&y);x^=pre;int tt=x;
			x=New[x];
			int t=find(p[x].fa).fa;
			f[t].cnt--;p[++n]=p[t];p[n].fa=n;
			if (s[0]=='L') p[n].y-=y;
			else if (s[0]=='R') p[n].y+=y;
			else if (s[0]=='U') p[n].x-=y;
			else p[n].x+=y;
			Add(p[n].x,p[n].y,p[n].fa);
			New[tt]=n;
		}
	}
}
	return 0;
}

