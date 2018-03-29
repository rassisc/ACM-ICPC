#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 110;

int n, m, a[N][N], p[10010], dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

int get(int x) {
    return x == p[x] ? p[x] : p[x] = get(p[x]);
}

int main() {

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < n * m; i++) {
        p[i] = i;
    }

    int ans = 5;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                int x = i + dx[k];
                int y = j + dy[k];
                if (x < 0 || x >= n || y < 0 || y >= m) {
                    continue;
                }
                if (a[i][j] == a[x][y]) {
                    int u = get(i * m + j);
                    int v = get(x * m + y);
                    if (u != v) {
                        p[v] = u;
                    }
                }
            }
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m;) {
            if (a[i - 1][j] < a[i][j]) {
                j++;
                ans++;
                while (j < m && max(a[i - 1][j], a[i - 1][j - 1]) < min(a[i][j], a[i][j - 1])) {
                    j++;
                }
            } else if (a[i - 1][j] > a[i][j]) {
                j++;
                ans++;
                while (j < m && min(a[i - 1][j], a[i - 1][j - 1]) > max(a[i][j], a[i][j - 1])) {
                    j++;
                }
            } else {
                j++;
            }
        }
    }

    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n;) {
            if (a[j][i - 1] < a[j][i]) {
                j++;
                ans++;
                while (j < n && max(a[j][i - 1], a[j - 1][i - 1]) < min(a[j][i], a[j - 1][i])) {
                    j++;
                }
            } else if (a[j][i - 1] > a[j][i]) {
                j++;
                ans++;
                while (j < n && min(a[j][i - 1], a[j - 1][i - 1]) > max(a[j][i], a[j - 1][i])) {
                    j++;
                }
            } else {
                j++;
            }
        }
    }

    for (int i = 0; i < n * m; i++) {
        int u = get(i);
        if (i == u) {
            ans++;
        }
    }

    printf("%d\n", ans);

    return 0;

}
