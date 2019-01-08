
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

const int kMaxN = 50000 + 2; // TO BE FIXED
const int kMaxD = 19;
const int kMaxL = 35;
const short kMod = 10007;

void Add(short& dest, short src) {
  dest += src;
  if (dest >= kMod) {
    dest -= kMod;
  }
}

std::vector<int> neighbors[kMaxN];
int go[kMaxN][kMaxD], depth[kMaxN], father[kMaxN];
int n, q;

void Traverse(std::vector<int>& order) {
  std::queue<int> queue;
  queue.push(1);
  father[1] = 0;

  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    order.push_back(u);

    int p = father[u];
    depth[u] = depth[p] + 1;
    go[u][0] = p;
    for (int d = 0; go[u][d]; ++ d) {
      go[u][d + 1] = go[go[u][d]][d];
    }

    for (int i = 0; i < neighbors[u].size(); ++ i) {
      int v = neighbors[u][i];
      if (v != father[u]) {
        queue.push(v);
        father[v] = u;
      }
    }
  }
}

int Jump(int u, int d) {
  for (int i = kMaxD - 1; i >= 0; -- i) {
    if (1 << i <= d) {
      d -= 1 << i;
      u = go[u][i];
    }
  }
  return u;
}

int GetLCA(int u, int v) {
  if (depth[u] < depth[v]) {
    std::swap(u, v);
  }
  u = Jump(u, depth[u] - depth[v]);
  for (int d = kMaxD - 1; d >= 0; -- d) {
    if (go[u][d] != go[v][d]) {
      u = go[u][d];
      v = go[v][d];
    }
  }
  return u == v ? u : go[u][0];
}

char mode[kMaxL], value[kMaxN];
int len_mode;
short frontways[kMaxN][kMaxL][kMaxL], backways[kMaxN][kMaxL][kMaxL];
short dp_front[kMaxL], dp_back[kMaxL];

// depth[w] <= depth[u]
// The path from u to w which covers mode[1, pivot] as a subsequence
int ComputeFrontWays(int u, int w, int pivot) {
  if (pivot < 1) {
    return dp_front[pivot] = 1;
  }
  short& result = dp_front[pivot];
  result = frontways[u][1][pivot];
  if (w == 1) {  // w == root
    return result;
  }

  for (int a = 0; a <= pivot - 1; ++ a) {
    result = ((int)result - (int)dp_front[a] *
        frontways[father[w]][a + 1][pivot]) % kMod;
  }
  result = (result + kMod) % kMod;
  return result;
}

// depth[w] <= depth[u]
// The path from u to w which covers mode[pivot, len_mode] as a subsequence
int ComputeBackWays(int u, int w, int pivot) {
  if (pivot > len_mode) {
    return dp_back[pivot] = 1;
  }
  short& result = dp_back[pivot];
  result = backways[u][pivot][len_mode];
  if (w == 1) {
    return result;
  }

  for (int a = pivot + 1; a <= len_mode + 1; ++ a) {
    result = ((int)result - (int)dp_back[a] *
        backways[father[w]][pivot][a - 1]) % kMod;
  }
  result = (result + kMod) % kMod;
  return result;
}

void Initialize() {
  memset(go, 0, sizeof(go));
  for (int node = 0; node < kMaxN; ++ node) {
    neighbors[node].clear();
  }
}

int main() {
  int test_count;
  assert(scanf("%d", &test_count) == 1);
  assert(1 <= test_count && test_count <= 10);
  while (test_count --) {
    Initialize();
    assert(scanf("%d%d", &n, &q) == 2);
    assert(1 <= n && n <= 50000);
    assert(1 <= q && q <= 50000);
    for (int i = 1; i < n; ++ i) {
      int u, v;
      assert(scanf("%d%d", &u, &v) == 2);
      assert(1 <= u && u <= n);
      assert(1 <= v && v <= n);
      neighbors[u].push_back(v);
      neighbors[v].push_back(u);
    }

    std::vector<int> order;
    Traverse(order);

    assert(scanf("%s%s", value + 1, mode + 1) == 2);
    int len_value = strlen(value + 1);
    len_mode = strlen(mode + 1);
    assert(len_value == n);
    assert(1 <= len_mode && len_mode <= 30);

    // Compute front-cover and back-cover ways to root
    // Order: from root to children
    for (int iter = 0; iter < order.size(); ++ iter) {
      int node = order[iter];
      for (int i = 1; i <= len_mode; ++ i) {
        frontways[node][i][i] = backways[node][i][i] = value[node] == mode[i];
        Add(frontways[node][i][i], frontways[father[node]][i][i]);
        Add(backways[node][i][i], backways[father[node]][i][i]);
      }
      for (int length = 2; length <= len_mode; ++ length) {
        for (int i = 1; i + length - 1 <= len_mode; ++ i) {
          int j = i + length - 1;
          frontways[node][i][j] = frontways[father[node]][i][j];  // father[root] == 0
          backways[node][i][j] = backways[father[node]][i][j];
          if (mode[i] == value[node]) {
            Add(frontways[node][i][j], frontways[father[node]][i + 1][j]);
          }
          if (mode[j] == value[node]) {
            Add(backways[node][i][j], backways[father[node]][i][j - 1]);
          }
        }
      }
    }

    // Deal with the queries
    while (q --) {
      int start, end;
      assert(scanf("%d%d", &start, &end) == 2);
      assert(1 <= start && start <= n);
      assert(1 <= end && end <= n);
      int lca = GetLCA(start, end);
      int ways = 0;
      if (lca == end) {
        for (int pivot = 0; pivot <= len_mode; ++ pivot) {
          ComputeFrontWays(start, lca, pivot);
        }
        ways = dp_front[len_mode];
      } else {
        for (int pivot = 0; pivot <= len_mode; ++ pivot) {
          ComputeFrontWays(start, lca, pivot);
        }
        int prev = Jump(end, depth[end] - depth[lca] - 1);
        for (int pivot = len_mode + 1; pivot >= 1; -- pivot) {
          ComputeBackWays(end, prev, pivot);
        }
        for (int pivot = 0; pivot <= len_mode; ++ pivot) {
          ways = (ways + (int)dp_front[pivot] *
              dp_back[pivot + 1]) % kMod;  // check if it should be fixed
        }
      }
      printf("%d\n", ways);
    }
  }
  return 0;
}

