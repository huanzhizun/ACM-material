#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <utility>

#define MAX 2048
#define INF 1e16

using namespace std;

const double eps = 1e-8;

double dp[2][MAX], q[MAX];
int que[MAX], front, rear;

inline bool check1(int x, int i, int j, double k) {
    return (dp[x][i] - dp[x][j]) / (double)(i - j) <= k;
}

inline bool check2(int x, int i, int j, int k) {
    return (dp[x][i] - dp[x][j]) / (double)(i - j) <= (dp[x][j] - dp[x][k]) / (double)(j - k);
}

double solve(int n, int k, double p) {
    int i, j, x;
    double ret;

    if (k > n) k = n;
    memset(dp, 0, sizeof(dp));
    for (i = n - 1; ~i; --i) dp[0][i] = dp[0][i + 1] + p;
    for (ret = dp[0][0], x = i = 1; i <= k; ++i, x ^= 1) {
        dp[x][n] = 0; front = rear = 0; que[rear++] = n - i + 1;
        for (j = n - i; ~j; --j) {
            while (front + 1 < rear && check1(x ^ 1, que[front + 1], que[front], -q[j])) ++front;
            dp[x][j] = dp[x ^ 1][que[front]] + (double)(que[front] - j) * q[j];
            ret = max(ret, dp[x][j] + (j ? (double)j * p : 0));

            //printf("i = %d, j = %d, pre = %d, dp = %f, ret = %f, q = %f\n", i, j, que[front], pow(10, dp[x][j]), pow(10, ret), q[j]);
            //getchar();

            while (front + 1 < rear && check2(x ^ 1, j, que[rear - 1], que[rear - 2])) --rear;
            que[rear++] = j;
        }
    }

    return ret;
}

int main() {
    int t, n, k, i, y;
    double p, ans, x;

    freopen("data5.in", "r", stdin);
    freopen("data5.out", "w", stdout);

    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%lf", &n, &k, &p);
        p = log10(1 - p);
        for (i = 0; i < n; ++i) {
            scanf("%lf", &q[i]);
            q[i] = log10(1 - q[i]);
        }
        ans = solve(n, k, p);

        if (ans < -INF) {
            x = 0; y = 0;
        } else {
            y = (int)floor(ans); x = pow(10, ans - y);
        }
        printf("%.4f %d\n", x, y);
    }

    return 0;
}
