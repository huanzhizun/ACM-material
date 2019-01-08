#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;

#define MAXN 2005
#define MAXK 2005
//���и���k<=1000�Ǵ���ģ�������������2000

int n, m;
double p;
double q[MAXN], arr[MAXN];
double lgdp[MAXK][MAXN];  
int front, back, queue[MAXN];
/*
lgdp[i][j]��i�����ң������������j���ʱ�Ľ����
lgdp[i][j] = max{lgdp[i-1][k] + (k-j) * lg(1-q[j])}
��lg(1-q[j])Ϊarr[j]����ôarr[j]�����ݼ�(j�ǵ���ɨ���)
��i�㣬�������k1>k2����k2���ڣ������ڣ�k1����ô
lgdp[i-1][k1] + (k1-j) * arr[j] <= lgdp[i-1][k2] + (k2-j) * arr[j]
��Ϊi��һ��Ҫö�ٵģ�����Ϊ����д��f[k]==lgdp[i-1][k]
��ô�ɵ�f[k2] - f[k1] >= (k2 - k1) * (-arr[j]) ����б��(f[k2] - f[k1]) / (k2 - k1) <= -arr[j]
������k2,k1������������ʽ����ô�Ե�ǰ���Ժ��j����Ȼk2����k1
������������������Ĳ���ʽ����ôk2һ������k1�𣿲�һ������Ϊ-arr[j]�ǵ���������
���������õ�������ά��

����Ԫ��һ��ʼΪ0��
ÿ�μ���dpʱҪ�Ӷ���ȡԪ�أ�����ζ��ױȶ��׺ã���ô����ֱ�ӵ������У��Ժ�Ҳ��������ˣ���������β�õ�����ά��ʱ���Եõ���ǰ���Ž⡣
��β��������������ԭ���Ķ�β��x,y���¼���Ķ�β��z�������ǰy��xҪ����ܱ�֤�Ժ�yҲ��x�
�������xyб�ʴ���yzб�ʣ���ô�Ժ����xyб��С��-arr[j]����ôyzб��Ҳһ��С��-arr[j]���Ӷ�zһ����y�ã����ǿ���ɾ��y

�����������̿������Ϊһ��б�ʵ�����ֱ����һ������͹���͹����ɨ��ɨ���ĵ�һ�����������Ž�㡣
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

//����ļ���
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

//�Ż��ļ���
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
			//ǰ���޳�
			while(front < back && (lgdp[i-1][queue[front]] - lgdp[i-1][queue[front+1]]) <= (-arr[j]) * (queue[front] - queue[front+1]))
			{
				front++;
			}
			//����ѡ��
			k = queue[front];
			lgdp[i][j] = lgdp[i-1][k] + (k - j) * arr[j];
			//͹��άϵ
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
