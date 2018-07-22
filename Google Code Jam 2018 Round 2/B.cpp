#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int M = 20;
const int N = 510;

int T, n, m, dp[N][N][M + 1][M + 1], res[N][N];

void update(int &x, int y) {
    x = max(x, y);
}

int main() {

    for (int i = 0; i <= 500; i++) {
        for (int j = 0; j <= 500; j++) {
            for (int k = 0; k <= M; k++) {
                for (int l = 0; l <= M; l++) {
                    dp[i][j][k][l] = -1;
                }
            }
        }
    }

    dp[0][0][0][0] = 0;

    for (int i = 0; i <= 500; i++) {
        for (int j = 0; j <= 500; j++) {
            for (int k = 0; k <= M; k++) {
                for (int l = 0; l <= M; l++) {
                    if (dp[i][j][k][l] == -1) {
                        continue;
                    }
                    res[i][j] = max(res[i][j], dp[i][j][k][l]);
                    if (k + 1 <= M) {
                        update(dp[i][j][k + 1][0], dp[i][j][k][l]);
                    }
                    if (l + 1 <= M) {
                        update(dp[i][j][k][l + 1], dp[i][j][k][l]);
                    }
                    if (i + k <= 500 && j + l <= 500 && k + l != 0) {
                        if (l + 1 <= M) {
                            update(dp[i + k][j + l][k][l + 1], dp[i][j][k][l] + 1);
                        } else if (l == M && k + 1 <= M) {
                            update(dp[i + k][j + l][k + 1][0], dp[i][j][k][l] + 1);
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i <= 500; i++) {
        for (int j = 0; j <= 500; j++) {
            if (i != 0) {
                res[i][j] = max(res[i][j], res[i - 1][j]);
            }
            if (j != 0) {
                res[i][j] = max(res[i][j], res[i][j - 1]);
            }
        }
    }

    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d %d", &n, &m);
        printf("Case #%d: %d\n", t, res[n][m]);
    }

    return 0;

}
