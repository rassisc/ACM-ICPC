#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000;

int T, n, m, r, c, d[N][N], a[2][N][N];
char s[N];
vector <int> g[2];

bool valid(int h, int cut, int n, int m, int at) {
    int now = 0;
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            now += a[at][i][j];
        }
        if (now > h) {
            return false;
        }
        if (now == h) {
            tmp++;
            now = 0;
            g[at].push_back(i);
        }
    }
    return now == 0 && tmp == cut;
}

int sum(int x1, int y1, int x2, int y2) {
    int ret = d[x2][y2];
    if (x1 != 0) {
        ret -= d[x1 - 1][y2];
    }
    if (y1 != 0) {
        ret -= d[x2][y1 - 1];
    }
    if (x1 != 0 && y1 != 0) {
        ret += d[x1 - 1][y1 - 1];
    }
    return ret;
}

bool check(int h) {
    for (int i = 0; i < g[0].size(); i++) {
        int x1 = (i == 0) ? 0 : (g[0][i - 1] + 1);
        int x2 = g[0][i];
        for (int j = 0; j < g[1].size(); j++) {
            int y1 = (j == 0) ? 0 : (g[1][j - 1] + 1);
            int y2 = g[1][j];
            if (sum(x1, y1, x2, y2) != h) {
                return false;
            }
        }
    }
    return true;
}

int main() {

    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d %d %d %d", &n, &m, &r, &c);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            for (int j = 0; j < m; j++) {
                a[0][i][j] = (s[j] == '@') ? 1 : 0;
                a[1][j][i] = a[0][i][j];
                sum += a[0][i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                d[i][j] = a[0][i][j];
                if (i != 0) {
                    d[i][j] += d[i - 1][j];
                }
                if (j != 0) {
                    d[i][j] += d[i][j - 1];
                }
                if (i != 0 && j != 0) {
                    d[i][j] -= d[i - 1][j - 1];
                }
            }
        }
        int k = (r + 1) * (c + 1);
        if (sum == 0) {
            printf("Case #%d: POSSIBLE\n", t);
        } else if (sum % k != 0 || !valid(sum / (r + 1), r + 1, n, m, 0) || !valid(sum / (c + 1), c + 1, m, n, 1)) {
            printf("Case #%d: IMPOSSIBLE\n", t);
        } else if (!check(sum / k)) {
            printf("Case #%d: IMPOSSIBLE\n", t);
        } else {
            printf("Case #%d: POSSIBLE\n", t);
        }
        g[0].clear();
        g[1].clear();
    }

    return 0;

}
