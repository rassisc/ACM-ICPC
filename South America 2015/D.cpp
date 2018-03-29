#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100;

int n, m, x, a[N];

int main() {

    scanf("%d %d", &n, &m);

    int ans = 0;

    for (int i = 0; i < m; i++) {
        scanf("%d", &x);
        int s = 0;
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[j]);
            s += a[j];
        }
        if (s <= x) {
            ans -= a[0];
        }
        for (int j = 10000; j >= 1; j /= 10) {
            if (s - a[0] + j <= x) {
                ans += j;
                break;
            }
        }
    }

    printf("%d\n", ans);

    return 0;

}
