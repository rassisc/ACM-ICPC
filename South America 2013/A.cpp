#include <queue>
#include <vector>
#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

const int N = 15000;
const int INF = (int) 1e9;

int n, d[N], r[110][110], c[110][110];
char s[110][110];
bool mark[N];
queue <int> q;
vector < pair < int, pair <int, int> > > g[N];

void add(int from, int to, int w) {
    int x = g[from].size();
    int y = g[to].size();
    g[from].push_back(make_pair(to, make_pair(w, y)));
    g[to].push_back(make_pair(from, make_pair(0, x)));
}

bool bfs(int from, int to) {
    for (int i = 0; i <= to; i++) {
        d[i] = -1;
        mark[i] = false;
    }
    d[from] = 0;
    q.push(from);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < g[now].size(); i++) {
            int tmp = g[now][i].first;
            if (d[tmp] == -1 && g[now][i].second.first > 0) {
                d[tmp] = d[now] + 1;
                q.push(tmp);
            }
        }
    }
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
                flow -= val;
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

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
    }

    pair <int, int> id = {0, 0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n;) {
            if (s[i][j] == 'X') {
                j++;
            } else if (s[i][j] == '.') {
                int k = j;
                while (k < n && s[i][k] == '.') {
                    k++;
                }
                for (int p = j; p < k; p++) {
                    r[i][p] = id.first;
                }
                id.first++;
                j = k;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n;) {
            if (s[j][i] == 'X') {
                j++;
            } else if (s[j][i] == '.') {
                int k = j;
                while (k < n && s[k][i] == '.') {
                    k++;
                }
                for (int p = j; p < k; p++) {
                    c[p][i] = id.second;
                }
                id.second++;
                j = k;
            }
        }
    }

    for (int i = 1; i <= id.first; i++) {
        add(0, i, 1);
    }

    for (int i = id.first + 1; i <= id.first + id.second; i++) {
        add(i, id.first + id.second + 1, 1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == '.') {
                add(r[i][j] + 1, id.first + c[i][j] + 1, 1);
            }
        }
    }

    int ans = 0;

    while (bfs(0, id.first + id.second + 1)) {
        ans += dfs(0, id.first + id.second + 1, INF);
    }

    printf("%d\n", ans);

    return 0;

}
