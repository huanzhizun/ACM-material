#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#define rep(i,s,t) for (int i = s; i <= t; ++i)
#define per(i,s,t) for (int i = s; i >= t; --i)
using namespace std;
int n, k, ans, N, K;
int A[1010];
int a[1010], b[1010][2], c[1010];
int q[1010], vis[1010], t, tt, T;
void Dfs2(int o){
	if (o == k+1){
		++T; int x = 0, y = 0;
		rep(i,1,k) x^=c[i];
		rep(i,1,k){
			y = 0;
			rep(j,i,k){
				y^=c[j];
				vis[y] = T; vis[y^x] = T;
			}
		}
		int res = K-1;
		while (vis[res+1] == T) ++res;
		if (res >= K) ans = max(ans, res);
		return;
	}
	rep(i,1,N)
	if (b[i][1]){
		c[o] = b[i][0]; --b[i][1];
		Dfs2(o+1);
		++b[i][1];
	}
}
void Dfs1(int o, int S){
	if (o == k+1){
		q[t = 1] = 0;
		rep(i,1,k){
			tt = t;
			rep(j,1,t) q[++tt] = q[j]^a[i];
			t = tt;
		}
		++T;
		rep(i,1,tt) vis[q[i]] = T;
		rep(i,K,ans+1) if (vis[i] != T) return;
		N = 0;
		rep(i,1,k){
			if (a[i] != a[i-1]) b[++N][0] = a[i], b[N][1] = 0;
			++b[N][1];
		}
		c[1] = b[1][0]; --b[1][1]; Dfs2(2);
		return;
	}
	rep(i,S,n) { a[o] = A[i]; Dfs1(o+1, i+1); }
}
inline void Run(){
	rep(i,1,n) scanf("%d", &A[i]);
	sort(A+1, A+n+1);
	ans = 0;
	Dfs1(1, 1);
	printf("%d\n", ans);
}
int main(){
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	while (scanf("%d%d%d", &n, &k, &K)!=EOF) Run();
	return clock();
}
