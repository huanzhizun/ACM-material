#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;

#define MAXN 2005
#define MAXK 2005
//题中给定k<=1000是错误的，用例最大给到了2000

int n, m;
double p;
double q[MAXN], arr[MAXN];
double lgdp[MAXK][MAXN];  
int front, back, queue[MAXN];
/*
lgdp[i][j]有i块奶酪，且这块奶酪在j点吃时的解对数
lgdp[i][j] = max{lgdp[i-1][k] + (k-j) * lg(1-q[j])}
令lg(1-q[j])为arr[j]，那么arr[j]单调递减(j是倒着扫描的)
对i点，假设决策k1>k2并且k2优于（或不劣于）k1，那么
lgdp[i-1][k1] + (k1-j) * arr[j] <= lgdp[i-1][k2] + (k2-j) * arr[j]
因为i是一定要枚举的，所以为化简写成f[k]==lgdp[i-1][k]
那么可得f[k2] - f[k1] >= (k2 - k1) * (-arr[j]) 或者斜率(f[k2] - f[k1]) / (k2 - k1) <= -arr[j]
因此如果k2,k1满足上述不等式，那么对当前和以后的j，当然k2优于k1
但是如果不满足这样的不等式，那么k2一定劣于k1吗？不一定，因为-arr[j]是单调递增的
所以我们用单调队列维护

队首元素一开始为0。
每次计算dp时要从队首取元素，如果次队首比队首好，那么队首直接弹出队列（以后也不会更好了），这样队尾得到合适维护时可以得到当前最优解。
队尾我们这样：假设原来的队尾是x,y，新加入的队尾是z，如果当前y比x要差，不能保证以后y也比x差。
但是如果xy斜率大于yz斜率，那么以后，如果xy斜率小于-arr[j]，那么yz斜率也一定小于-arr[j]，从而z一定比y好，于是可以删掉y

于是整个过程可以理解为一条斜率递增的直线在一个向下凸起的凸包上扫，扫到的第一个顶点是最优解点。
*/

void input()
{
	int i;

	scanf("%d%d%lf",&n,&m,&p);
	for(i=0;i<n;i++)
	{
		scanf("%lf",&q[i]);
		arr[i] = log10(1 - q[i]);
	}
}

//最初的计算
void oricalc()
{
	int i, j, k;
	double x, e, lgp;

	if(p >= 1.0 && (q[0] >= 1.0 || m == 0))
	{
		printf("%.4lf %d\n",0.0,0);
		return ;
	}
	lgdp[0][n] = 0.0;
	if(p >= 1.0)
	{
		for(i=0;i<n;i++)
			lgdp[0][i] = -DBL_MAX;
	}else{
		lgp = log10(1 - p);
		for(i=0;i<n;i++)
			lgdp[0][i] = (n - i) * lgp;
	}
	for(i=1;i<=m;i++)
	{
		for(j=0;j<=n;j++)
		{
			lgdp[i][j] = lgdp[i-1][j];
			for(k=j+1;k<=n;k++)
			{
				lgdp[i][j] = max(lgdp[i][j], lgdp[i-1][k] + (k - j) * arr[j]);
			}
		}
	}

	x = lgdp[m][0];
	if(p < 1.0)
	{
		for(i=0;i<n;i++)
		x = max(x, lgdp[m][i] + i * lgp);
	}
	x = modf(x, &e);
	x += 1.0;
	j = (int)(e - 1);
	x = pow(10.0, x);
	printf("%.4lf %d\n",x,j);
}

//优化的计算
void dpcalc()
{
	int i, j, k, x, y, z;
	double xx, e, lgp;

	if(p >= 1.0 && (q[0] >= 1.0 || m == 0))
	{
		printf("%.4lf %d\n",0.0,0);
		return ;
	}
	lgdp[0][n] = 0.0;
	if(p >= 1.0)
	{
		for(i=0;i<n;i++)
			lgdp[0][i] = -DBL_MAX;
	}else{
		lgp = log10(1 - p);
		for(i=0;i<n;i++)
			lgdp[0][i] = (n - i) * lgp;
	}

	for(i=1;i<=m;i++)
	{
		front = back = 0;
		queue[0] = n;
		lgdp[i][n] = lgdp[i-1][n];
		for(j=n-1;j>=0;j--)
		{
			//前置剔除
			while(front < back && (lgdp[i-1][queue[front]] - lgdp[i-1][queue[front+1]]) <= (-arr[j]) * (queue[front] - queue[front+1]))
			{
				front++;
			}
			//最优选择
			k = queue[front];
			lgdp[i][j] = lgdp[i-1][k] + (k - j) * arr[j];
			//凸包维系
			z = j;
			while(front < back)
			{
				x = queue[back-1];
				y = queue[back];
				if((lgdp[i-1][x] - lgdp[i-1][y]) * (y - z) >= (x - y) * (lgdp[i-1][y] - lgdp[i-1][z]))
					back--;
				else
					break;
			}
			back++;
			queue[back] = z;
		}
	}

	xx = lgdp[m][0];
	if(p < 1.0)
	{
		for(i=0;i<n;i++)
		xx = max(xx, lgdp[m][i] + i * lgp);
	}
	
	xx = modf(xx, &e);
	xx += 1.0;
	j = (int)(e - 1);
	xx = pow(10.0, xx);
	printf("%.4lf %d\n",xx,j);
}

int main()
{
	int t;

	scanf("%d",&t);
	while(t--)
	{
		input();
		//oricalc();
		dpcalc();
	}
	return 0;
}
