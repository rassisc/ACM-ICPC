#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, x, y, m, p[18][N], d[N];
long long s[N];

int lca(int x, int y) {
    if (d[x] > d[y]) {
        swap(x, y);
    }
    int v = d[y] - d[x];
    for (int i = 17; i >= 0; i--) {
        if ((v & (1 << i)) != 0) {
            y = p[i][y];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = 17; i >= 0; i--) {
        if (p[i][x] != p[i][y]) {
            x = p[i][x];
            y = p[i][y];
        }
    }
    return p[0][x];
}

int main() {

    for (int t = 1; scanf("%d", &n) != EOF; t++) {
        if (n == 0) {
            break;
        }
        s[0] = 0;
        d[0] = 0;
        p[0][0] = 0;
        for (int i = 1; i < n; i++) {
            scanf("%d %d", &p[0][i], &x);
            d[i] = d[p[0][i]] + 1;
            s[i] = s[p[0][i]] + x;
        }
        for (int j = 1; j < 18; j++) {
            for (int i = 0; i < n; i++) {
                p[j][i] = p[j - 1][p[j - 1][i]];
            }
        }
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            int l = lca(x, y);
            long long ans = s[x] + s[y] - 2LL * s[l];
            printf("%lld%c", ans, (i + 1 == m) ? '\n' : ' ');
        }
    }

    return 0;

}
