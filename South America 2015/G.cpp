#include <queue>
#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10010;
const double INF = 1e17;

int n, m, u[N], v[N], a[N], b[N];
bool mark[N];
double d[N];
queue <int> q;
vector <int> g[N];

double calc(double mid) {
    for (int i = 0; i < n; i++) {
        d[i] = INF;
        mark[i] = false;
    }
    q.push(0);
    d[0] = 0.0;
    mark[0] = true;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        mark[now] = false;
        for (int i = 0; i < g[now].size(); i++) {
            int id = g[now][i];
            int tmp = u[id] + v[id] - now;
            double cost = d[now] + a[id] * mid + b[id];
            if (cost < d[tmp]) {
                d[tmp] = cost;
                if (!mark[tmp]) {
                    q.push(tmp);
                    mark[tmp] = true;
                }
            }
        }
    }
    return d[n - 1];
}

int main() {

    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &u[i], &v[i], &a[i], &b[i]);
        u[i]--;
        v[i]--;
        g[u[i]].push_back(i);
        g[v[i]].push_back(i);
    }

    double low = 0;
    double high = 24 * 60;

    for (int it = 0; it < 100; it++) {
        double rl = low + (high - low) / 3.0;
        double rr = high - (high - low) / 3.0;
        if (calc(rl) < calc(rr)) {
            low = rl;
        } else {
            high = rr;
        }
    }

    printf("%.5f\n", calc(low));

    return 0;

}
