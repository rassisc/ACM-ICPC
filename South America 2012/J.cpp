#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m, u, v, l[N], f[N], p[N], d[N], a[N], h[N], s[N], w[17][N];
bool seen[N];
vector <int> q;
vector <int> g[N];

int find(int x) {
    return x == p[x] ? p[x] : p[x] = find(p[x]);
}

int lca(int u, int v) {
    if (h[u] > h[v]) {
        swap(u, v);
    }
    int k = h[v] - h[u];
    for (int i = 16; i >= 0; i--) {
        if ((k & (1 << i)) != 0) {
            v = w[i][v];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 16; i >= 0; i--) {
        if (w[i][u] != w[i][v]) {
            u = w[i][u];
            v = w[i][v];
        }
    }
    return w[0][u];
}

int main() {

    for (int t = 1; scanf("%d", &n) != EOF; t++) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &f[i]);
            f[i]--;
        }
        for (int i = 0; i < n; i++) {
            p[i] = i;
            d[i] = 0;
            seen[i] = false;
        }
        for (int i = 0; i < n; i++) {
            d[f[i]]++;
        }
        for (int i = 0; i < n; i++) {
            h[i] = 0;
            w[0][i] = i;
        }
        for (int i = 0; i < n; i++) {
            int u = find(i);
            int v = find(f[i]);
            if (u != v) {
                p[v] = u;
            }
        }
        for (int i = 0; i < n; i++) {
            int c = find(i);
            g[c].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            int c = find(i);
            if (seen[c]) {
                continue;
            }
            seen[c] = true;
            for (int j = 0; j < g[c].size(); j++) {
                int now = g[c][j];
                if (d[now] == 0) {
                    q.push_back(now);
                }
            }
            for (int j = 0; j < q.size(); j++) {
                int now = q[j];
                if (--d[f[now]] == 0) {
                    q.push_back(f[now]);
                }
            }
            for (int j = q.size() - 1; j >= 0; j--) {
                int now = q[j];
                w[0][now] = f[now];
                if (d[f[now]] == 0) {
                    a[now] = a[f[now]];
                    h[now] = h[f[now]] + 1;
                } else {
                    h[now] = 1;
                    a[now] = f[now];
                }
            }
            s[c] = g[c].size() - q.size();
            for (int j = 0; j < g[c].size(); j++) {
                int now = g[c][j];
                if (d[now] != 0) {
                    int pre = now;
                    l[now] = 1;
                    while (f[pre] != now) {
                        l[f[pre]] = l[pre] + 1;
                        pre = f[pre];
                    }
                    break;
                }
            }
            q.clear();
        }
        for (int i = 1; i <= 16; i++) {
            for (int j = 0; j < n; j++) {
                w[i][j] = w[i - 1][w[i - 1][j]];
            }
        }
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &u, &v);
            u--;
            v--;
            if (find(u) != find(v)) {
                puts("-1");
            } else if (d[u] > 0 && d[v] > 0) {
                int c = find(u);
                if (l[u] > l[v]) {
                    swap(u, v);
                }
                printf("%d\n", min(l[v] - l[u], s[c] + l[u] - l[v]));
            } else if (d[u] == 0 && d[v] == 0 && a[u] == a[v]) {
                int par = lca(u, v);
                printf("%d\n", h[u] + h[v] - 2 * h[par]);
            } else {
                int ans = 0;
                if (d[u] == 0) {
                    ans += h[u];
                    u = a[u];
                }
                if (d[v] == 0) {
                    ans += h[v];
                    v = a[v];
                }
                if (l[u] > l[v]) {
                    swap(u, v);
                }
                ans += min(l[v] - l[u], s[find(u)] + l[u] - l[v]);
                printf("%d\n", ans);
            }
        }
        for (int i = 0; i < n; i++) {
            g[i].clear();
        }
    }

    return 0;

}
