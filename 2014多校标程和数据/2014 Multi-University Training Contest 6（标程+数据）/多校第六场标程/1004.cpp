#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <assert.h>
using namespace std;
#define MAXN 25
#define INF 0x3f3f3f3f

int n, m, CA_max, PA_max;
int Num[200], add[MAXN][MAXN];
int DF, MF, ST, GK;
struct node {
    int id;
    int num, CA_max;
    bool pos[4];
    int CA[4], PA[4];
}player[MAXN];
int in[MAXN];
bool cmp(node a, node b) {
    return a.CA_max > b.CA_max;
}

int trans(char *s) {
    if (strcmp(s, "DF") == 0) return 0;
    else if (strcmp(s, "MF") == 0) return 1;
    else if (strcmp(s, "ST") == 0) return 2;
    else if (strcmp(s, "GK") == 0) return 3;
    return -1;
}

int dpCA[15][11][11][2], dpPA[15][11][11][2];

void update(int i, int mf, int st, int gk, int ca, int pa) {
    if (mf > MF || st > ST || gk > GK || mf + st + gk < i - DF) return;
    if (dpCA[i][mf][st][gk] < ca) {
        dpCA[i][mf][st][gk] = ca;
        dpPA[i][mf][st][gk] = pa;
    } else if (dpCA[i][mf][st][gk] == ca)
        dpPA[i][mf][st][gk] = max(dpPA[i][mf][st][gk], pa);
}

void DP() {
    int tmp1 = 0, tmp2 = 0, num[4] = {0};
    for (int i = 0; i < 11; i ++) {
        for (int j = 0; j < 11; j ++)
            tmp1 += add[in[i]][in[j]];
        tmp2 += player[in[i]].CA_max;
        for (int j = 0; j < 4; j ++)
            if (player[in[i]].pos[j]) num[j]++;
    }
    if (num[0] < DF || num[1] < MF || num[2] < ST || num[3] < GK) return;
    if (tmp1 + tmp2 < CA_max) return;

    for (int i = 0;i <= 11; i ++)
        for (int mf = 0; mf <= MF; mf ++)
            for (int st = 0; st <= ST; st ++)
                for (int gk = 0; gk <= 1; gk ++)
                    dpCA[i][mf][st][gk] = dpPA[i][mf][st][gk] = -INF;
    dpCA[0][0][0][0] = tmp1;
    dpPA[0][0][0][0] = 0;
    for (int i = 1; i <= 11; i ++) {
        int t = in[i - 1];
        for (int mf = 0; mf <= MF; mf ++)
            for (int st = 0; st <= ST; st ++)
                for (int gk = 0; gk <= 1; gk ++)
                    if (dpCA[i - 1][mf][st][gk] != -INF && dpPA[i - 1][mf][st][gk] != -INF) {
                        int ca = dpCA[i - 1][mf][st][gk];
                        int pa = dpPA[i - 1][mf][st][gk];
                        if (player[t].pos[0]) update(i, mf, st, gk, ca + player[t].CA[0], pa + player[t].PA[0]);
                        if (player[t].pos[1]) update(i, mf + 1, st, gk, ca + player[t].CA[1], pa + player[t].PA[1]);
                        if (player[t].pos[2]) update(i, mf, st + 1, gk, ca + player[t].CA[2], pa + player[t].PA[2]);
                        if (player[t].pos[3]) update(i, mf, st, gk + 1, ca + player[t].CA[3], pa + player[t].PA[3]);
                    }
    }
    if (dpCA[11][MF][ST][GK] > CA_max) {
        CA_max = dpCA[11][MF][ST][GK];
        PA_max = dpPA[11][MF][ST][GK];
    }
    else if (dpCA[11][MF][ST][GK] == CA_max && dpCA[11][MF][ST][GK] != -INF)
        PA_max = max(PA_max, dpPA[11][MF][ST][GK]);
}

void dfs(int tot,int x) {
    if (tot == 11) {
        DP();
        return;
    }
    if (x > n) return;
    in[tot] = x;
    dfs(tot + 1, x + 1);
    if (11 - tot <= n - x)
        dfs(tot, x + 1);
}

int M[4];
void prework() {
    M[0] = 0, M[1] = 1, M[2] = 2;
    if (DF < MF) {
        swap(M[0], M[1]);
        swap(DF, MF);
    }
    if (DF < ST) {
        swap(M[0], M[2]);
        swap(DF, ST);
    }
    if (MF < ST) {
        swap(M[1], M[2]);
        swap(MF, ST);
    }
    int temp1[4], temp2[4];
    bool temp3[4];
    for (int i = 1; i <= n; ++ i) {
        memcpy(temp1, player[i].CA, sizeof(temp1));
        memcpy(temp2, player[i].PA, sizeof(temp2));
        memcpy(temp3, player[i].pos, sizeof(temp3));
        for (int j = 0; j < 3; ++ j) {
            player[i].CA[j] = temp1[M[j]];
            player[i].PA[j] = temp2[M[j]];
            player[i].pos[j] = temp3[M[j]];
        }
    }
}

int main() {
    //freopen("data.in", "r", stdin);
    int cas, u, v, val;
    char tmp[10];
    scanf("%d", &cas);
    while (cas --) {
        scanf("%d", &n);
        memset(add, 0, sizeof(add));
        memset(Num, 0, sizeof(Num));
        for (int i = 1; i <= n; i ++) {
            int ca, pa;
            player[i].CA_max = -INF;
            scanf("%d%d", &player[i].id, &player[i].num);
            memset(player[i].pos, 0, sizeof(player[i].pos));
            for (int j = 0; j < player[i].num; j ++) {
                scanf("%s", tmp);
                int p = trans(tmp);
                assert(p >= 0);
                scanf("%d%d", &player[i].CA[p], &player[i].PA[p]);
                player[i].pos[p] = 1;
                player[i].CA_max = max(player[i].CA_max, player[i].CA[p]);
            }

        }
        sort(player + 1, player + n + 1, cmp);
        for (int i = 1; i <= n; i ++) {
            assert(Num[player[i].id] == 0);
            Num[player[i].id] = i;
        }
        scanf("%d",&m);
        while (m--) {
            scanf("%d%d%s%d", &u, &v, tmp, &val);
            if (tmp[0] == 'D') val = -val;
            add[Num[u]][Num[v]] += val;
        }
        CA_max = PA_max = -INF;
        GK = 1;
        scanf("%d-%d-%d", &DF, &MF, &ST);
        prework();
        dfs(0, 1);
        if (CA_max == -INF) printf("Poor Manager!\n");
        else printf("%d %d\n", CA_max, PA_max);
    }
    return 0;
}

