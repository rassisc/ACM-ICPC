#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;
const int MOD = (int) 1e9 + 7;

int c[N], dp[11][55][11][11];
char w[N];
long long comb[N][N];

void add(int &x, long long y) {
    x += (int) y;
    if (x >= MOD) {
        x -= MOD;
    }
}

long long choose(int n, int k) {
    if (k > n) {
        return 0LL;
    }
    return comb[n][k];
}

int main() {

    memset(comb, 0, sizeof comb);

    for (int i = 0; i < N; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
            if (comb[i][j] >= MOD) {
                comb[i][j] -= MOD;
            }
        }
    }

    scanf("%s", w);

    string s = w;
    int n = s.size();
    int x = (n + 1) / 2;
    int y = n - x;

    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= x; j++) {
            for (int p = 0; p < 11; p++) {
                for (int q = 0; q < 11; q++) {
                    dp[i][j][p][q] = 0;
                }
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        c[i] = 0;
    }

    for (int i = 0; i < s.size(); i++) {
        c[s[i] - '0']++;
    }

    for (int i = 0; i <= min(x, c[0]); i++) {
        int j = c[0] - i;
        if (j <= y) {
            add(dp[1][x - i][0][0], choose(n / 2, i) * choose((n - 1) / 2, j) % MOD);
        }
    }

    int now = c[0];

    for (int i = 1; i < 10; i++) {
        for (int j = 0; j <= x; j++) {
            if (now < x - j || y < now - (x - j)) {
                continue;
            }
            int k = y - (now - (x - j));
            for (int p = 0; p < 11; p++) {
                for (int q = 0; q < 11; q++) {
                    if (dp[i][j][p][q] == 0) {
                        continue;
                    }
                    for (int odd = 0; odd <= min(j, c[i]); odd++) {
                        int even = c[i] - odd;
                        if (even <= k) {
                            int np = (p + odd * i) % 11;
                            int nq = (q + even * i) % 11;
                            long long val = (choose(j, odd) * choose(k, even) % MOD) * dp[i][j][p][q] % MOD;
                            add(dp[i + 1][j - odd][np][nq], val);
                        }
                    }
                }
            }
        }
        now += c[i];
    }

    int res = 0;

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            int r = (i + j * 10) % 11;
            if (r == 0) {
                res += dp[10][0][i][j];
                if (res >= MOD) {
                    res -= MOD;
                }
            }
        }
    }

    printf("%d\n", res);

    return 0;

}
