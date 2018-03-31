#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = (int) 1e9;

int n, m, x, s[10010][1010];

int main() {

    for (int t = 1; scanf("%d", &n) != EOF; t++) {
        if (n == 0) {
            break;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= 1000; j++) {
                s[i][j] = 0;
            }
            scanf("%d", &m);
            for (int j = 0; j < m; j++) {
                scanf("%d", &x);
                s[i][x]++;
            }
            for (int j = 1; j <= 1000; j++) {
                s[i][j] += s[i][j - 1];
            }
        }
        int ans = INF;
        for (int mid = 0; mid <= 1000; mid++) {
            int now = 0;
            for (int i = 0; i < n; i++) {
                int v = mid == 0 ? 0 : s[i][mid - 1];
                now += abs(v - (s[i][1000] - v));
            }
            ans = min(ans, now);
        }
        printf("%d\n", ans);
    }

    return 0;

}
