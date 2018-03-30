#include <map>
#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 300000;

int n, m, x[N], y[N], d[N];
bool seen[N];
map <int, int> h;
vector <int> q;
vector <int> g[N];
vector < pair <int, int> > p;

int main() {

    for (int t = 1; scanf("%d %d", &n, &m) != EOF; t++) {
        if (n + m == 0) {
            break;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x[i], &y[i]);
            if (h.count(x[i]) == 0) {
                int s = h.size();
                h[x[i]] = s;
            }
            if (h.count(y[i]) == 0) {
                int s = h.size();
                h[y[i]] = s;
            }
        }
        for (int i = 0; i < m; i++) {
            x[i] = h[x[i]];
            y[i] = h[y[i]];
            if (x[i] > y[i]) {
                swap(x[i], y[i]);
            }
            p.push_back({x[i], y[i]});
        }
        sort(p.begin(), p.end());
        p.resize(unique(p.begin(), p.end()) - p.begin());
        int k = h.size();
        for (int i = 0; i < k; i++) {
            d[i] = 0;
        }
        for (int i = 0; i < p.size(); i++) {
            int a = p[i].first;
            int b = p[i].second;
            d[a]++;
            d[b]++;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        if (k == 0) {
            puts("Y");
        } else if (*max_element(d, d + k) > 2) {
            puts("N");
        } else {
            bool possible = true;
            for (int i = 0; i < k; i++) {
                seen[i] = false;
                g[i].push_back(k);
                sort(g[i].begin(), g[i].end());
            }
            for (int i = 0; i < k; i++) {
                if (seen[i]) {
                    continue;
                }
                q.push_back(i);
                seen[i] = true;
                for (int j = 0; j < q.size(); j++) {
                    int now = q[j];
                    for (int r = 0; r < g[now].size(); r++) {
                        int tmp = g[now][r];
                        if (tmp < k && !seen[tmp]) {
                            seen[tmp] = true;
                            q.push_back(tmp);
                            break;
                        }
                    }
                }
                int id = q[q.size() - 1];
                if (q.size() >= 3 && *lower_bound(g[id].begin(), g[id].end(), i) == i && q.size() != n) {
                    possible = false;
                }
                for (int j = 0; j < q.size(); j++) {
                    int now = q[j];
                    for (int r = 0; r < g[now].size(); r++) {
                        int tmp = g[now][r];
                        if (tmp < k && !seen[tmp]) {
                            seen[tmp] = true;
                            q.push_back(tmp);
                        }
                    }
                }
                q.clear();
            }
            puts(possible ? "Y" : "N");
        }
        h.clear();
        p.clear();
        for (int i = 0; i < k; i++) {
            g[i].clear();
        }
    }

    return 0;

}
