#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m, x, y, a[N];

int gcd(int x, int y) {
    x = abs(x);
    y = abs(y);
    while (y > 0) {
        int t = x % y;
        x = y;
        y = t;
    }
    return x;
}

int main() {

    for (int t = 1; scanf("%d %d", &n, &m) != EOF; t++) {
        if (n + m == 0) {
            break;
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        int g = abs(2 * a[0]);
        for (int i = 0; i < n; i++) {
            g = gcd(g, 2 * a[i]);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            if (n == 1) {
                printf("%c", 2 * a[0] - x == y ? 'Y' : 'N');
            } else if ((y - x) % g == 0) {
                printf("Y");
            } else if ((y - (g - x)) % g == 0) {
                printf("Y");
            } else {
                printf("N");
            }
            printf("%c", (i + 1 == m) ? '\n' : ' ');
        }
    }

    return 0;

}
