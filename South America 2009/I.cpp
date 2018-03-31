#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, x[N], y[N];
long long a[N];

int main() {

    for (int t = 1; scanf("%d", &n) != EOF; t++) {
        if (n == 0) {
            break;
        }
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x[i], &y[i]);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int dx = x[i] - x[j];
                int dy = y[i] - y[j];
                a[j] = 1LL * dx * dx + 1LL * dy * dy;
            }
            sort(a, a + n);
            for (int j = 0; j < n;) {
                int k = j;
                while (k < n && a[j] == a[k]) {
                    k++;
                }
                int d = k - j;
                ans += d * (d - 1) / 2;
                j = k;
            }
        }
        printf("%d\n", ans);
    }

    return 0;

}
