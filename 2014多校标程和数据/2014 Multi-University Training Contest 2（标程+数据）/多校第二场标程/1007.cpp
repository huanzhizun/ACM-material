#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define LL long long
using namespace std;
struct node
{
	int vis[26],fail,end;
	void init()
	{
		memset(vis,0,sizeof(vis));fail=0;end=1;
	}
}a[45];
int t1[45][45],t2[1][45],tot,P[3]={179,173,163},Prime[50],Now,n,Which,PP=5047621,ans[3],X,Y,xx[3],M[3];
LL L;
queue<int> h;
struct ma1
{
	int a[45][45];
	void Mul(int b[45][45])
	{
		memset(t1,0,sizeof(t1));
		for(int i=0;i<=tot;i++)
			for(int j=0;j<=tot;j++)
				for(int k=0;k<=tot;k++) t1[i][k]=t1[i][k]+a[i][j]*b[j][k];
		for(int i=0;i<=tot;i++)
			for(int j=0;j<=tot;j++) a[i][j]=t1[i][j]%P[Which];
	}
}tmp[185],T;
struct ma2
{
	int a[1][45];
	void Mul(int b[45][45])
	{
		memset(t2,0,sizeof(t2));
		for(int i=0;i<1;i++)
			for(int j=0;j<=tot;j++)
				for(int k=0;k<=tot;k++) t2[i][k]=t2[i][k]+a[i][j]*b[j][k];
		for(int i=0;i<1;i++)
			for(int j=0;j<=tot;j++) a[i][j]=t2[i][j]%P[Which];
	}
}Ans;
char s[45][45];
bool ss(int n)
{
	for(int i=2;i*i<=n;i++)
		if (n%i==0) return 0;
	return 1;
}
void read(int &x)
{
	char ch=getchar();int mark=1;for(;ch!='-'&&(ch<'0'||ch>'9');ch=getchar());if (ch=='-') mark=-1,ch=getchar();
	for(x=0;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-48;x*=mark;
}
void Make_Trie(int k,char s[45])
{
	int u=0,l=strlen(s);
	for(int i=0;i<l;i++)
	{
		int t=s[i]-65;
		if (!a[u].vis[t]) 
		{
			a[u].vis[t]=++tot;a[tot].init();
		}
		u=a[u].vis[t];
	}
	a[u].end=a[u].end*Prime[k]*(Now+l)%P[Which];
}
void Make_Fail()
{
	h.push(0);
	while (h.size())
	{
		int u=h.front();
		for(int i=0;i<26;i++)
			if (a[u].vis[i])
			{
				int v=a[u].vis[i],p=a[u].fail;
				if (u)
				{
					a[v].fail=a[p].vis[i];
					(a[v].end*=a[a[v].fail].end)%=P[Which];
				}
				else a[v].fail=0;
				h.push(v);
			}
			else 
				if (u) a[u].vis[i]=a[a[u].fail].vis[i];
		h.pop();	
	}
}
int Cal()
{
	bool F=0;
	for(Now=1;Now<=P[Which];Now++)
	{
		a[0].init();tot=0;
		for(int i=1;i<=n;i++) Make_Trie(i,s[i]);
		Make_Fail();
		for(int i=0;i<=tot;i++)
			for(int j=0;j<=tot;j++) tmp[Now].a[i][j]=0;
		for(int i=0;i<=tot;i++)
			for(int j=0;j<26;j++) (tmp[Now].a[i][a[i].vis[j]]+=a[a[i].vis[j]].end)%=P[Which];
		if (F) T.Mul(tmp[Now].a);
		else
		{
			F=1;
			for(int i=0;i<=tot;i++)
				for(int j=0;j<=tot;j++) T.a[i][j]=tmp[Now].a[i][j];
		}
	}
	for(int i=0;i<=tot;i++) Ans.a[0][i]=0;
	Ans.a[0][0]=1;
	LL t=L/P[Which];
	while (t)
	{
		if (t&1) Ans.Mul(T.a);
		T.Mul(T.a);t>>=1;
	}
	for(int i=1;i<=L%P[Which];i++) Ans.Mul(tmp[i].a);
	int ans=0;
	for(int i=0;i<=tot;i++) (ans+=Ans.a[0][i])%=P[Which];
	return ans;
}
void Gcd(int a,int b)
{
	if (b==0)
	{
		X=1;Y=0;return;
	}
	Gcd(b,a%b);
	int t1=X,t2=Y;
	X=t2;Y=t1-a/b*t2;
}
#include<ctime>
int main()
{
	//freopen("zcc loves words.in","r",stdin);
	//freopen("zcc loves words.out","w",stdout);
	//freopen("a.in","r",stdin);
	int c=0,te=0;
	for(int i=2;i<=200;i++)
		if (ss(i)) Prime[++c]=i;
	M[0]=P[1]*P[2];M[1]=P[0]*P[2];M[2]=P[0]*P[1];
	Gcd(M[0],P[0]);xx[0]=X;
	Gcd(M[1],P[1]);xx[1]=X;
	Gcd(M[2],P[2]);xx[2]=X;
	while (scanf("%d%I64d",&n,&L)!=EOF)
	{
		for(int i=1;i<=n;i++) scanf("%s",s[i]);
		int Ans=0;
		for(Which=0;Which<3;Which++) Ans=(((LL)Cal()*xx[Which]%PP*M[Which]%PP)+Ans)%PP;
		printf("Case #%d: %d\n",++te,(Ans+PP)%PP);
	}
	return clock();
}

