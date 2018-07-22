#include <cstdio>
#include <vector>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 400;
const int INF = (int) 1e9;

int T, n, d[N], a[N][N], cap[N][N];
bool mark[N];
vector <int> q;
vector <int> g[N];
vector < pair <int, int> > u[N];

void add_edge(int from, int to, int c) {
    cap[from][to] = c;
    cap[to][from] = 0;
    g[from].push_back(to);
    g[to].push_back(from);
}

bool bfs(int from, int to) {
    for (int i = 0; i <= to; i++) {
        d[i] = -1;
        mark[i] = false;
    }
    d[from] = 0;
    q.push_back(from);
    for (int i = 0; i < q.size(); i++) {
        int now = q[i];
        for (int j = 0; j < g[now].size(); j++) {
            int tmp = g[now][j];
            if (d[tmp] == -1 && cap[now][tmp] > 0) {
                d[tmp] = d[now] + 1;
                q.push_back(tmp);
            }
        }
    }
    q.clear();
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
        int tmp = g[from][i];
        if (d[tmp] == d[from] + 1 && cap[from][tmp] > 0) {
            int val = dfs(tmp, to, min(flow, cap[from][tmp]));
            if (val != 0) {
                res += val;
                flow -= val;
                cap[from][tmp] -= val;
                cap[tmp][from] += val;
            }
            if (flow == 0) {
                return res;
            }
        }
    }
    return res;
}

int main() {

    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &a[i][j]);
                a[i][j] += n;
                u[a[i][j]].push_back({i, j});
            }
        }
        int res = 0;
        for (int i = 0; i <= 2 * n; i++) {
            if (u[i].size() == 0) {
                continue;
            }
            vector <int> vx;
            vector <int> vy;
            for (int j = 0; j < u[i].size(); j++) {
                int x = u[i][j].first;
                int y = u[i][j].second;
                vx.push_back(x);
                vy.push_back(y);
            }
            sort(vx.begin(), vx.end());
            sort(vy.begin(), vy.end());
            vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
            vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
            for (int j = 0; j < u[i].size(); j++) {
                int x = lower_bound(vx.begin(), vx.end(), u[i][j].first) - vx.begin();
                int y = lower_bound(vy.begin(), vy.end(), u[i][j].second) - vy.begin();
                add_edge(x + 1, vx.size() + y + 1, 1);
            }
            for (int j = 1; j <= vx.size(); j++) {
                add_edge(0, j, 1);
            }
            for (int j = 1; j <= vy.size(); j++) {
                add_edge(vx.size() + j, vx.size() + vy.size() + 1, 1);
            }
            int now = 0;
            while (bfs(0, vx.size() + vy.size() + 1)) {
                now += dfs(0, vx.size() + vy.size() + 1, INF);
            }
            res += u[i].size() - now;
            u[i].clear();
            for (int j = 0; j <= vx.size() + vy.size() + 1; j++) {
                g[j].clear();
            }
        }
        printf("Case #%d: %d\n", t, res);
    }

    return 0;

}
