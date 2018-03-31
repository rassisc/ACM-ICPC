#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 200;

int n, r, c, k, a[N][N], b[N][N], dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

int main() {

    for (int t = 1; scanf("%d %d %d %d", &n, &r, &c, &k) != EOF; t++) {
        if (n + r + c + k == 0) {
            break;
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        for (int it = 0; it < k; it++) {
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    b[i][j] = a[i][j];
                    for (int d = 0; d < 4; d++) {
                        int x = i + dx[d];
                        int y = j + dy[d];
                        if (0 <= x && x < r && 0 <= y && y < c && (a[x][y] + 1) % n == a[i][j]) {
                            b[i][j] = a[x][y];
                            break;
                        }
                    }
                }
            }
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    a[i][j] = b[i][j];
                }
            }
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                printf("%d%c", a[i][j], (j + 1 == c) ? '\n' : ' ');
            }
        }
    }

    return 0;

}
