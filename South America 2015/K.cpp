#include <set>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100010;
const int INF = (int) 2e9;

int n, m, e[N], l[N], r[N], s[N], c[N], dp[N];
set < pair <int, int> > now;
vector <int> g[N];
vector < pair <int, int> > h[N];

int main() {

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &e[i]);
    }

    for (int i = 1; i < n; i++) {
        e[i] += e[i - 1];
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &l[i], &s[i], &c[i]);
        l[i]--;
        int low = l[i];
        int high = n - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            int val = e[mid] - (l[i] == 0 ? 0 : e[l[i] - 1]);
            if (val <= s[i]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        r[i] = high;
        g[l[i]].push_back(i);
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = INF;
    }

    now.insert({0, m});
    h[0].push_back({0, m});

    for (int i = 0; i <= n; i++) {
        if (now.empty()) {
            continue;
        }
        int val = (*now.begin()).first;
        dp[i] = val;
        for (int j = 0; j < g[i].size(); j++) {
            int id = g[i][j];
            if (l[id] > r[id]) {
                continue;
            }
            now.insert({dp[i] + c[id], id});
            h[r[id] + 1].push_back({dp[i] + c[id], id});
        }
        for (int j = 0; j < h[i].size(); j++) {
            now.erase(h[i][j]);
        }
    }

    printf("%d\n", dp[n] == INF ? -1 : dp[n]);

    return 0;

}
