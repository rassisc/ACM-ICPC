#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 400;
const int MOD = (int) 1e8;

int m, n, a[N], b[N], ways[N][N];
vector <int> v;

int main() {

    for (int t = 1; scanf("%d %d", &m, &n) != EOF; t++) {
        if (m + n == 0) {
            break;
        }
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &a[i], &b[i]);
            v.push_back(a[i]);
            v.push_back(b[i]);
        }
        v.push_back(0);
        v.push_back(m);
        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());
        m = v.size() - 1;
        for (int i = 0; i < n; i++) {
            a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
            b[i] = lower_bound(v.begin(), v.end(), b[i]) - v.begin();
        }
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= m; j++) {
                ways[i][j] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i] == 0 && b[j] > b[i] && a[j] <= b[i] && a[j] > a[i]) {
                    ways[b[i]][b[j]] += 1;
                }
            }
        }
        for (int i = 0; i <= m; i++) {
            for (int j = i + 1; j <= m; j++) {
                for (int k = 0; k < n; k++) {
                    if (b[k] > j && a[k] <= j && a[k] > i) {
                        ways[j][b[k]] += ways[i][j];
                        if (ways[j][b[k]] >= MOD) {
                            ways[j][b[k]] -= MOD;
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 0 && b[i] == m) {
                ans++;
            }
        }
        for (int i = 0; i < m; i++) {
            ans += ways[i][m];
            if (ans >= MOD) {
                ans -= MOD;
            }
        }
        printf("%d\n", ans);
        v.clear();
    }

    return 0;

}
