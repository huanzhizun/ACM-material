#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    int cas;
    scanf("%d", &cas);
    while (cas --) {
        scanf("%d%d", &n, &m);
        if (n > m) swap(n, m);
        if (n == 1 && m == 1)
            printf("1\n");
        else if (n == 1)
            printf("%d\n", 2 * (m - 1));
        else
            printf("%d\n", 8 * (n - 1) * (m - 1));
    }
    return 0;
}
