#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2000;
const int INF = (int) 1e9;

int n, m, k, u, v, s[50], c[50][50], d[N];
char op;
bool mark[N];
vector <int> o;
vector < pair < int, pair <int, int> > > g[N];

void add(int from, int to, int flow) {
    int p = g[from].size();
    int q = g[to].size();
    g[from].push_back({to, make_pair(flow, q)});
    g[to].push_back({from, make_pair(0, p)});
}

bool bfs(int from, int to) {
    for (int i = 0; i <= to; i++) {
        d[i] = -1;
        mark[i] = false;
    }
    d[from] = 0;
    o.push_back(from);
    for (int i = 0; i < o.size(); i++) {
        int now = o[i];
        for (int j = 0; j < g[now].size(); j++) {
            int tmp = g[now][j].first;
            if (g[now][j].second.first > 0 && d[tmp] == -1) {
                o.push_back(tmp);
                d[tmp] = d[now] + 1;
            }
        }
    }
    o.clear();
    return d[to] != -1;
}

int dfs(int from, int to, int flow) {
    if (from == to) {
        return flow;
    }
    if (mark[from]) {
        return 0;
    }
    mark[from] = true;
    int res = 0;
    for (int i = 0; i < g[from].size(); i++) {
        int tmp = g[from][i].first;
        if (d[tmp] == d[from] + 1 && g[from][i].second.first > 0) {
            int val = dfs(tmp, to, min(flow, g[from][i].second.first));
            if (val != 0) {
                res += val;
                flow -= tmp;
                g[from][i].second.first -= val;
                g[tmp][g[from][i].second.second].second.first += val;
            }
            if (flow == 0) {
                return res;
            }
        }
    }
    return res;
}

int main() {

    for (int t = 1; scanf("%d %d %d", &n, &m, &k) != EOF; t++) {
        if (n + m + k == 0) {
            break;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                c[i][j] = m;
            }
        }
        for (int i = 0; i < n; i++) {
            s[i] = 0;
        }
        for (int i = 0; i < k; i++) {
            scanf("%d %c %d", &u, &op, &v);
            if (op == '<') {
                s[v] += 2;
            } else if (op == '=') {
                s[u] += 1;
                s[v] += 1;
            }
            if (u > v) {
                swap(u, v);
            }
            c[u][v]--;
        }
        for (int i = 1; i < n; i++) {
            while (c[0][i] > 0) {
                s[0] += 2;
                c[0][i]--;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (c[i][j] != 0) {
                    add(0, i * n + j + 1, 2 * c[i][j]);
                    add(i * n + j + 1, n * n + i + 1, 2 * c[i][j]);
                    add(i * n + j + 1, n * n + j + 1, 2 * c[i][j]);
                }
            }
        }
        bool possible = true;
        for (int i = 1; i < n; i++) {
            if (s[i] >= s[0]) {
                possible = false;
                break;
            }
            add(n * n + i + 1, n * n + n + 1, s[0] - s[i] - 1);
        }
        if (!possible) {
            puts("N");
        } else {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    sum += 2 * c[i][j];
                }
            }
            while (bfs(0, n * n + n + 1)) {
                sum -= dfs(0, n * n + n + 1, INF);
            }
            puts(sum <= 0 ? "Y" : "N");
        }
        for (int i = 0; i <= n * n + n + 1; i++) {
            g[i].clear();
        }
    }

    return 0;

}
