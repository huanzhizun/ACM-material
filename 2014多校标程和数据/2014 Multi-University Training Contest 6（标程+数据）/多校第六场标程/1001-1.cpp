#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <assert.h>
using namespace std;
#define MAXN 10050

int n, m;
int fa[MAXN], son[MAXN], val[MAXN], level[MAXN];
int f[15][MAXN], cnt;
double sum, ways;

void dp() {
    for (int i = 0; i < 1000; ++ i) {
        int num = 0;
        for (int j = 0; j < cnt; ++ j)
            if (f[j][i] != -1) num ++;
        if (!num) break;
        for (int j = 1; j < (1 << cnt); ++ j) {
            double s = 0, w = 1;
            int y = 0;
            for (int k = 0; k < cnt; ++ k)
                if (j & (1 << k)) {
                    if (f[k][i] == -1) {
                        s = 0;
                        break;
                    }
                    s += val[f[k][i]];
                    w *= level[k] - i + 1;
                    y ++;
                } else w *= min(i, level[k] + 1) + 1;

            sum += s * w;
            if (y > 1) sum += y * s / num * w;

        }
    }
}

int main() {
    //freopen("data.in", "r", stdin);
    //freopen("data.out", "w", stdout);
    int ncase;
    scanf("%d", &ncase);
    while (ncase--) {
        scanf("%d%d", &n, &m);
        assert(n <= 10000 && m <= 10000);
        for (int i = 0; i < n; ++ i)    scanf("%d", &val[i]);
        int a, b;
        memset(fa, 0, sizeof(fa));
        memset(son, -1, sizeof(son));
        memset(f, -1, sizeof(f));
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", &a, &b);
            assert(0 <= a && a < n && 0 <= b && b < n);
            fa[b] = 1;
            son[a] = b;
        }
        sum = 0, ways = 1;
        cnt = 0;
        for (int i = 0; i < n; ++ i)
            if (!fa[i]) {
                int k = 0;
                for (int j = i; j != -1; j = son[j], k += 1) {
                    f[cnt][k] = j;
                }
                ways *= (k + 1);
                level[cnt ++] = k - 1;
                assert(k <= 1000);
            }
        assert(cnt <= 10);
        dp();
        printf("%.3f\n", sum / (ways - 1));
    }
    return 0;
}
