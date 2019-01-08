#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define LL long long
using namespace std;
struct node
{
	int x,y,d,brk;
};
queue<node> h;
int n,m,w1[30][30],w2[30][30],xx[4]={-1,0,1,0},yy[4]={0,1,0,-1},L[30][30][4],x,inf=1000000000,Min,dis[30][30][4][2],sx,sy,ex,ey;
bool vis[30][30][4][2];
void read(int &x)
{
	char ch=getchar();int mark=1;for(;ch!='-'&&(ch<'0'||ch>'9');ch=getchar());if (ch=='-') mark=-1,ch=getchar();
	for(x=0;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-48;x*=mark;
}
node make(int x,int y,int d,int brk)
{
	node tmp;tmp.x=x;tmp.y=y;tmp.d=d;tmp.brk=brk;return tmp;
}
bool check(int x,int y){return x&&y&&x<=n&&y<=m;}
bool right(int pre,int now){return ((pre+1)&3)==now;}
void Spfa1(int x,int y,int time)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<4;k++)
				for(int l=0;l<2;l++) vis[i][j][k][l]=0,dis[i][j][k][l]=-inf;
	for(int i=0;i<4;i++) h.push(make(x,y,i,0)),vis[x][y][i][0]=1,dis[x][y][i][0]=time;
	while (h.size())
	{
		node u=h.front();h.pop();int x=u.x,y=u.y,d=u.d,brk=u.brk,time=dis[x][y][d][brk];vis[x][y][d][brk]=0;
		int px=x-xx[d],py=y-yy[d];
		if (!check(px,py)) continue;
		for(int i=0;i<4;i++)
		{
			int x1=px-xx[i],y1=py-yy[i],add=brk,pre=time-L[px][py][d];
			if (pre>=0&&check(x1,y1))
			{
				if (pre>w1[px][py]&&w1[px][py]<w2[px][py])
				{
					int t=max(0,pre-w2[px][py]);
					if (pre-t>=0&&dis[px][py][i][add]<pre-t)
					{
						dis[px][py][i][add]=pre-t;
						if (!vis[px][py][i][add])
						{
							h.push(make(px,py,i,add));vis[px][py][i][add]=1;
						}
					}
				}
				if (!right(i,d)) add++;
				if (add<2&&dis[px][py][i][add]<pre)
				{
					dis[px][py][i][add]=pre;
					if (!vis[px][py][i][add])
					{
						h.push(make(px,py,i,add));vis[px][py][i][add]=1;
					}
				}
			}
		}
	}
}
void Spfa2(int x,int y,int time)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<4;k++)
				for(int l=0;l<2;l++) vis[i][j][k][l]=0,dis[i][j][k][l]=inf;
	for(int i=0;i<4;i++) h.push(make(x,y,i,0)),vis[x][y][i][0]=1,dis[x][y][i][0]=time;
	while (h.size())
	{
		node u=h.front();h.pop();int x=u.x,y=u.y,d=u.d,brk=u.brk,time=dis[x][y][d][brk];vis[x][y][d][brk]=0;
		for(int i=0;i<4;i++)
		{
			int x1=x+xx[i],y1=y+yy[i],add=brk;
			if (check(x1,y1))
			{
				if (w2[x][y]>=time&&w1[x][y]<w2[x][y])
				{
					int t=max(0,w1[x][y]+1-time);
					if (dis[x1][y1][i][add]>time+L[x][y][i]+t)
					{
						dis[x1][y1][i][add]=time+L[x][y][i]+t;
						if (!vis[x1][y1][i][add])
						{
							h.push(make(x1,y1,i,add));vis[x1][y1][i][add]=1;
						}
					}
				}
				if (!right(d,i)) add++;
				if (add<2&&dis[x1][y1][i][add]>time+L[x][y][i])
				{
					dis[x1][y1][i][add]=time+L[x][y][i];
					if (!vis[x1][y1][i][add])
					{
						h.push(make(x1,y1,i,add));vis[x1][y1][i][add]=1;
					}
				}
			}
		}
	}
}
void Do(int x,int y,int time)
{
	Spfa1(x,y,time);
	int ft[2];ft[0]=ft[1]=-inf;
	for(int i=0;i<4;i++)
		for(int j=0;j<2;j++) ft[j]=max(ft[j],dis[sx][sy][i][j]);
	Spfa2(x,y,time);
	int st[2];st[0]=st[1]=inf;
	for(int i=0;i<4;i++)
		for(int j=0;j<2;j++) st[j]=min(st[j],dis[ex][ey][i][j]);
	if (st[0]!=inf&&max(ft[0],ft[1])!=-inf) Min=min(Min,st[0]-max(ft[0],ft[1]));
	if (st[1]!=inf&&ft[0]!=-inf) Min=min(Min,st[1]-ft[0]);
	//printf("%d %d %d %d\n",Min,x,y,time);
}
int main()
{
    //freopen("zcc_loves_traffic_lights.in","r",stdin);freopen("zcc_loves_traffic_lights2.out","w",stdout);
	int te=0;
while (scanf("%d%d",&n,&m)!=EOF)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) read(w1[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) read(w2[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++) 
		{
			read(x);L[i][j][1]=L[i][j+1][3]=x;
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			read(x);L[i][j][2]=L[i+1][j][0]=x;
		}
	read(sx);read(sy);read(ex);read(ey);
	w1[sx][sy]=w1[ex][ey]=w1[1][1]=w1[1][m]=w1[n][1]=w1[n][m]=0;
	w2[sx][sy]=w2[ex][ey]=w2[1][1]=w2[1][m]=w2[n][1]=w2[n][m]=100000000;
	Min=inf;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) 
			if (w1[i][j]<w2[i][j])
			{
				Do(i,j,w1[i][j]+1);
				Do(i,j,w2[i][j]);
			}
	printf("Case #%d: ",++te);
	if (Min!=inf) printf("%d\n",Min);
	else printf("-1\n");
}
	return 0;
}

