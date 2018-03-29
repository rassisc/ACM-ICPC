#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 500;
const int INF = (int) 1e9;

int n, m, k, b, u, v, x[N], y[N], dp[N];
bool mark[N];
vector <int> g[N];
vector < pair < pair <int, int>, int > > p;

int calc() {
    for (int i = 0; i <= n + m; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;
    int ans = 0;
    for (int i = 0; i < p.size(); i++) {
        int A = p[i].first.first;
        int B = p[i].first.second;
        int d = B - A;
        ans += A;
        if (d <= 0) {
            continue;
        }
        for (int j = n + m; j >= d; j--) {
            if (dp[j - d] != INF) {
                dp[j] = min(dp[j], dp[j - d] + p[i].second);
            }
        }
    }
    for (int i = n + m; i >= 0; i--) {
        if (dp[i] <= b) {
            ans += i;
            break;
        }
    }
    return ans;
}

int main() {

    scanf("%d %d %d %d", &n, &m, &k, &b);

    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d", &y[i]);
    }

    for (int i = 0; i < k; i++) {
        scanf("%d %d", &u, &v);
        u--;
        v--;
        g[u].push_back(v + n);
        g[v + n].push_back(u);
    }

    for (int i = 0; i < n + m; i++) {
        mark[i] = false;
    }

    for (int i = 0; i < n + m; i++) {
        if (mark[i]) {
            continue;
        }
        pair < pair <int, int>, int > w = {{0, 0}, 0};
        queue <int> q;
        q.push(i);
        mark[i] = true;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            if (now < n) {
                w.first.first++;
                w.second += x[now];
            } else {
                w.first.second++;
                w.second += y[now - n];
            }
            for (int j = 0; j < g[now].size(); j++) {
                int tmp = g[now][j];
                if (!mark[tmp]) {
                    q.push(tmp);
                    mark[tmp] = true;
                }
            }
        }
        p.push_back(w);
    }

    printf("%d ", calc());

    for (int i = 0; i < p.size(); i++) {
        swap(p[i].first.first, p[i].first.second);
    }

    printf("%d\n", calc());

    return 0;

}
