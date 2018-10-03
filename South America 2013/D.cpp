#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m, u, v;
bool d[N][N];
vector <int> g[N];
vector < pair <int, int> > a;

int main() {

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = false;
        }
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        u--;
        v--;
        g[u].push_back(v);
    }

    for (int i = 1; i < n; i++) {
        d[0][i] = true;
        a.push_back({0, i});
    }

    for (int i = 0; i < n; i++) {
        sort(g[i].begin(), g[i].end());
    }

    for (int i = 0; i < a.size(); i++) {
        int x = a[i].first;
        int y = a[i].second;
        for (int j = g[x].size() - 1; j >= 0; j--) {
            int k = g[x][j];
            if (k <= max(x, y)) {
                break;
            }
            if (!d[k][y]) {
                d[k][y] = true;
                a.push_back({k, y});
            }
        }
        for (int j = g[y].size() - 1; j >= 0; j--) {
            int k = g[y][j];
            if (k <= max(x, y)) {
                break;
            }
            if (!d[x][k]) {
                d[x][k] = true;
                a.push_back({x, k});
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (d[i][j] || d[j][i]) {
                ans++;
            }
        }
    }

    printf("%d\n", ans);

    return 0;

}
