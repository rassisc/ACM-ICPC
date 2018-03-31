#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m, x, ans[N];
vector <int> g[N];

int main() {

    for (int t = 1; scanf("%d %d", &n, &m) != EOF; t++) {
        if (n + m == 0) {
            break;
        }
        n++;
        for (int i = 1; i < n; i++) {
            scanf("%d", &x);
            g[x].push_back(i);
        }
        for (int i = n - 1; i >= 0; i--) {
            if (g[i].size() == 0) {
                ans[i] = 1;
            } else {
                ans[i] = 0;
                int d = (g[i].size() * m + 99) / 100;
                vector <int> v;
                for (int j = 0; j < g[i].size(); j++) {
                    v.push_back(ans[g[i][j]]);
                }
                sort(v.begin(), v.end());
                for (int j = 0; j < d; j++) {
                    ans[i] += v[j];
                }
            }
        }
        printf("%d\n", ans[0]);
        for (int i = 0; i < n; i++) {
            g[i].clear();
        }
    }

    return 0;

}
