#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 300;
const int INF = (int) 1e9;

int n, m, k, x, d[N];
bool mark[N];
vector <int> o;
vector <int> a[N];
vector < pair < int, pair <int, int> > > g[N];

void add(int from, int to, int c) {
    int p = g[from].size();
    int q = g[to].size();
    g[from].push_back({to, make_pair(c, q)});
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
        int now = g[from][i].first;
        if (g[from][i].second.first > 0 && d[now] == d[from] + 1) {
            int tmp = dfs(now, to, min(flow, g[from][i].second.first));
            if (tmp != 0) {
                res += tmp;
                flow -= tmp;
                g[from][i].second.first -= tmp;
                g[now][g[from][i].second.second].second.first += tmp;
            }
            if (flow == 0) {
                return res;
            }
        }
    }
    return res;
}

int main() {

    scanf("%d %d", &n, &m);

    bool flag = true;

    for (int i = 0; i < n; i++) {
        scanf("%d", &k);
        flag &= (k < n);
        for (int j = 0; j < k; j++) {
            scanf("%d", &x);
            x--;
            a[i].push_back(x);
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            add(0, j + 1, 1);
            for (int p = 0; p < a[j].size(); p++) {
                add(j + 1, a[j][p] + n + 1, 1);
            }
        }
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &x);
            x--;
            add(x + n + 1, n + n + 1, 1);
        }
        if (k == 0) {
            puts(flag ? "Y" : "N");
        } else {
            int sum = 0;
            while (bfs(0, n + n + 1)) {
                sum += dfs(0, n + n + 1, INF);
            }
            puts(sum == k ? "Y" : "N");
        }
        for (int j = 0; j <= n + n + 1; j++) {
            g[j].clear();
        }
    }

    return 0;

}
