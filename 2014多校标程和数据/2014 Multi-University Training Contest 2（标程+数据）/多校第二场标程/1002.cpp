#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#define i64 long long
#define fortodo(i, f, t) for (i = f; i <= t; i++)
using namespace std;

const i64 Scale = 1000;

struct Bignum
{
	vector<i64> V;
	Bignum(i64 v = 0)
	{
		V.clear();
		V.push_back(v);
		while (V.back() >= Scale)
			{
				int nx = V.back() / Scale;
				V.back() %= Scale;
				V.push_back(nx);
			}
	}
	Bignum operator * (Bignum rhs)
	{
		Bignum ret;
		ret.V.clear();
		int lsz = V.size(), rsz = rhs.V.size(), tsz = lsz + rsz;
		ret.V.resize(tsz);
		int i, j;
		fortodo(i, 0, lsz - 1)
			fortodo(j, 0, rsz - 1)
				ret.V[i + j] += V[i] * rhs.V[j];
		fortodo(i, 0, tsz - 2) 
			{
				ret.V[i + 1] += ret.V[i] / Scale;
				ret.V[i] %= Scale;
			}
		while ((tsz > 1) && (ret.V.back() == 0))
			{
				tsz--;
				ret.V.pop_back();
			}
		return ret;
	}
	i64 operator % (i64 x)
	{
		int sz = V.size();
		i64 ret = 0;
		for (int i = sz - 1; i >= 0; i--)
			ret = (ret * Scale + V[i]) % x;
		return ret;
	}
	void operator /= (i64 x)
	{
		int sz = V.size();
		for (int i = sz - 1; i; i--)
			{
				V[i - 1] += (V[i] % x) * Scale;
				V[i] /= x;
			}
		V[0] /= x;
		while ((sz > 1) && (V.back() == 0))
			{
				sz--;
				V.pop_back();
			}
	}
	void Print()
	{
		int sz = V.size();
		printf("%d", int(V[sz - 1]));
		for (int i = sz - 2; i >= 0; i--)
			printf("%03d", int(V[i]));
	}
};

bool intGreater(int x, int y)
{
	return x > y;
}

vector<int> divisors;
int N, D;

void regi(int x)
{
	for (int i = 1; i * i <= x; i++)
		{
			divisors.push_back(i);
			divisors.push_back(x / i);
		}
}

Bignum bignumPow(Bignum bas, int T)
{
	Bignum ans(1);
	for (; T; T >>= 1)
		{
			if (T & 1) ans = ans * bas;
			bas = bas * bas;
		}
	return ans;
}

int main()
{
	//freopen("intersection.in", "r", stdin);
	//freopen("intersection.out","w",stdout);
	while (scanf("%d%d", &N, &D) != EOF)
		{
			divisors.clear();
			regi(9);
			regi(N);
			sort(divisors.begin(), divisors.end(), intGreater);
			divisors.resize(unique(divisors.begin(), divisors.end()) - divisors.begin());
			while (divisors.back() == 1) divisors.pop_back();
			Bignum P = Bignum((D * (D - 1)) / 2) * bignumPow(Bignum(N + 4), 2);
			Bignum Q = Bignum(9) * bignumPow(Bignum(N), D);
			for (vector<int>::iterator p = divisors.begin(); p != divisors.end(); p++)
				while ((P % *p == 0) && (Q % *p == 0))
					{
						P /= *p;
						Q /= *p;
					}
			if ((Q.V.size() == 1) && (Q.V[0] == 1))
				{
					P.Print();
					puts("");
				}
			else
				{
					P.Print();
					putchar('/');
					Q.Print();
					puts("");
				}
		}
}

