#include <cassert>
#include <cstdio>
#include <cstring>

const double EPS = 1E-8;

int sgn(double x) {
  return x < -EPS ? -1 : x > EPS;
}

const int N = 100000 + 10;

int elements[N], sum[N], queue[N], n;

bool CheckSmaller(int a1, int b1, int a2, int b2) {
  return ((long long)sum[b1] - sum[a1 - 1]) * (b2 - a2 + 1) >=
      ((long long)sum[b2] - sum[a2 - 1]) * (b1 - a1 + 1);
}

int main() {
  //freopen("input", "r", stdin);
  int test_count;
  assert(scanf("%d", &test_count) == 1);
  assert(1 <= test_count && test_count <= 100);
  while (test_count --) {
    assert(scanf("%d", &n) == 1);
    assert(1 <= n && n <= 100000);
    for (int i = 1; i <= n; ++ i) {
      assert(scanf("%d", elements + i) == 1);
      assert(0 == elements[i] || 1 == elements[i]);
      sum[i] = sum[i - 1] + elements[i];
    }

    int length = 0;
    for (int i = 1; i <= n; ++ i) {
      int id = i;
      while (length > 0 &&
          CheckSmaller(queue[length], id - 1, id, i)) {
        id = queue[length --];
      }
      queue[++ length] = id;
    }

    queue[++ length] = n + 1;
    double answer = 0;
    for (int i = 1; i < length; ++ i) {
      int lower = queue[i];
      int upper = queue[i + 1] - 1;
      double x = ((double)sum[upper] - sum[lower - 1]) / (upper - lower + 1);
      answer += sum[upper] - sum[lower - 1] + (upper - lower + 1) * x * x -
          2 * (sum[upper] - sum[lower - 1]) * x;
    }
    printf("%.6f\n", answer);
  }
  return 0;
}
