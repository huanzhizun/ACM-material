#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 1000 + 1;
const int Q = 20 + 1;
const int K = 50 + 1;

long long dp[K][Q], earn[K][N][Q], max_earn[K][Q], combine[N][N][Q];
long long property[K][4], base_value[Q];
int num_bank, num_person, num_funds, mod;

void Initialize() {
  for (int n0 = 1; n0 <= num_person; ++ n0) {
    int module = mod * (n0 + 1);

    combine[n0][0][0] = 1 % module;
    for (int n = 1; n <= num_person; ++ n) {
      combine[n0][n][0] = 1 % module;
      for (int q = 1; q <= std::min(n, num_funds); ++ q) {
        //combine[n0][n][q] = (combine[n0][n - 1][q - 1] + 
        //    combine[n0][n - 1][q]) % module;
        combine[n0][n][q] = combine[n0][n - 1][q - 1] + combine[n0][n - 1][q];
        if (combine[n0][n][q] >= module) combine[n0][n][q] -= module;
      }
    }
  }
}

void Calculate(long long earn[N][Q], long long* property, long long* max_earn) {
  long long delta = property[0];
  for (int q = 0; q <= num_funds; ++ q) {
    max_earn[q] = 0;
  }

  for (int n = 1; n <= num_person; ++ n) {
    int module = (n + 1) * mod; // NOTE mod == 1

    base_value[0] = 0;
    for (int q = 1; q <= num_funds; ++ q) {
      base_value[q] = (property[1] * base_value[q - 1] % module *
          base_value[q - 1] % module + property[2] *
          base_value[q - 1] % module + property[3]) % module;
    }

    for (int q = 1; q <= num_funds; ++ q) {
      earn[n][q] = 0; 
      for (int i = 0; q - i * delta >= 1; ++ i) { // NOTE n <= q
        (earn[n][q] += base_value[q - i * delta] * combine[n][n - 1][i]) %=
            module;
      }
      max_earn[q] = std::max(max_earn[q], earn[n][q] / (n + 1) % mod);
    }
  }
}

int main() {
  int test_count;
  assert(scanf("%d", &test_count) == 1);
  assert(1 <= test_count && test_count <= 10);
  while (test_count --) {
    scanf("%d%d%d%d", &num_person, &num_funds, &num_bank, &mod);
    Initialize();

    for (int i = 1; i <= num_bank; ++ i) {
      for (int j = 0; j < 4; ++ j) {
        std::cin >> property[i][j];
      }
    }

    dp[0][0] = 0;
    for (int bank_id = 1; bank_id <= num_bank; ++ bank_id) {
      Calculate(earn[bank_id], property[bank_id], max_earn[bank_id]);
      dp[bank_id][0] = 0;
      for (int spent_funds = 1; spent_funds <= num_funds; ++ spent_funds) {
        dp[bank_id][spent_funds] = dp[bank_id - 1][spent_funds];
        for (int use_funds = 0; use_funds <= spent_funds; ++ use_funds) {
          dp[bank_id][spent_funds] = std::max(dp[bank_id][spent_funds],
              dp[bank_id - 1][spent_funds - use_funds] +
              max_earn[bank_id][use_funds]);
        }
      }
    }

    long long answer = 0;
    for (int spent_funds = 0; spent_funds <= num_funds; ++ spent_funds) {
      answer = std::max(answer, dp[num_bank][spent_funds]);
    }
    std::cout << answer << '\n';
  }
  return 0;
}
