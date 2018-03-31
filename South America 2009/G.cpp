#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 510;

int n, m, k, l, r, a[N][N];

int main() {

    for (int t = 1; scanf("%d %d", &n, &m) != EOF; t++) {
        if (n + m == 0) {
            break;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        scanf("%d", &k);
        for (int i = 0; i < k; i++) {
            scanf("%d %d", &l, &r);
            int ans = 0;
            for (int j = 0; j < n; j++) {
                int p = lower_bound(a[j], a[j] + m, l) - a[j];
                if (p >= m || a[j][p] > r) {
                    continue;
                }
                int low = 1;
                int high = min(n - j, m - p);
                while (low <= high) {
                    int mid = (low + high) / 2;
                    if (a[j + mid - 1][p + mid - 1] <= r) {
                        low = mid + 1;
                    } else {
                        high = mid - 1;
                    }
                }
                ans = max(ans, high);
            }
            printf("%d\n", ans);
        }
        puts("-");
    }

    return 0;

}
