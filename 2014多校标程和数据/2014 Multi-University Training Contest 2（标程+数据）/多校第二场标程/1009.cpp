#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define LL long long
using namespace std;
int n,K,a[110][110],A,vis[110],te;
void read(int &x)
{
	char ch=getchar();int mark=1;for(;ch!='-'&&(ch<'0'||ch>'9');ch=getchar());if (ch=='-') mark=-1,ch=getchar();
	for(x=0;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-48;x*=mark;
}
int main()
{
    //freopen("zcc_loves_ranklist.in","r",stdin);freopen("zcc_loves_ranklist.out","w",stdout);
	while(scanf("%d%d",&n,&K)!=EOF)
	{
	printf("Case #%d:\n",++te);
	if ((K&1)==0) 
	{
		printf("0\n");
		for(int i=1;i<=n;i++) 
		{
			for(int j=1;j<=K;j++)
			{
				if (j&1) printf("%d",i);
				else printf("%d",n-i+1);
				if (j==K) printf("\n");
				else printf(" ");
			}
		}
	}
	else if (K==1)
	{
		printf("%d\n",n-1);
		for(int i=1;i<=n;i++) printf("%d\n",i);
	}
	else
	{
		if (n&1)
		{
			printf("0\n");
			for(int i=1;i<=n;i++) 
			{
				for(int j=1;j<K-2;j++)
				{
					if (j&1) printf("%d ",i);
					else printf("%d ",n-i+1); 
				}
				for(int j=K-2;j<=K;j++) 
				{
					if (j==K)
					{
						if (i<=(n+1)/2) printf("%d\n",n-i*2+2);
						else printf("%d\n",n-(i-n/2-1)*2+1);
					}
					else if (j&1) printf("%d ",i);
					else 
					{
						if (i>(n+1)/2) printf("%d ",i-(n+1)/2);
						else printf("%d ",i+n/2);
					}
				}
			}
		}
		else 
		{
			printf("1\n");
			for(int i=1;i<=n;i++) 
			{
				for(int j=1;j<K-2;j++)
				{
					if (j&1) printf("%d ",i);
					else printf("%d ",n-i+1); 
				}
				for(int j=K-2;j<=K;j++) 
				{
					if (j==K)
					{
						if (i<=n/2) printf("%d\n",n-i*2+2);
						else printf("%d\n",n-(i-n/2)*2+1);
					}
					else if (j&1) printf("%d ",i);
					else 
					{
						if (i>n/2) printf("%d ",i-n/2);
						else printf("%d ",i+n/2);
					}
				}
			}
		}
	}
	//printf("aaaasile\n");
	if (n&1) printf("No\n");
	else 
	{
		printf("Yes\n");
		if (n<=100)
		{
			for(int i=1;i<=n;i++) a[1][i]=i;
			for(int i=2;i<=n;i++) a[i][1]=i;
			for(int i=2;i<n;i++)
			{
				a[i][i]=1;
				int t=2;
				for(int j=i+1;j<=n;j++) 
				{
					if (t==i) a[i][j]=n;else a[i][j]=t;
					t++;
				}
				for(int j=2;j<i;j++)
				{
					if (t==i) a[i][j]=n;else a[i][j]=t;
					t++;
				}
			}
			for(int i=2;i<=n;i++) 
			{
				A++;
				for(int j=1;j<n;j++) vis[a[j][i]]=A;
				for(int j=1;j<=n;j++)
					if (vis[j]!=A) 
					{
						a[n][i]=j;break;
					}
			}
			/*for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=n;j++) printf("%d ",a[i][j]);
				printf("\n");
			}*/
			for(int i=1;i<=n;i++)
			{
				int st=i;
				printf("%d",i);
				for(int j=2;j<=n;j++)
				{
					printf(" %d",a[st][j]);st=a[st][j];
				}
				printf("\n");
			}
		}
	}
}
	return 0;
}

