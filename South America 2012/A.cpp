#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;
const long long INF = (long long) 1e18;

struct point {
    long long x;
    long long y;

    point(long long _x = 0, long long _y = 0) {
        x = _x;
        y = _y;
    }

    point operator - (const point &rhs) const {
        return point(x - rhs.x, y - rhs.y);
    }

    long long operator ^ (const point &rhs) const {
        return x * rhs.y - y * rhs.x;
    }
};

int n, m;
long long x[N], w[N], a[N], s[N], dp[N][N];
vector <point> hull;

int main() {

    for (int t = 1; scanf("%d %d", &n, &m) != EOF; t++) {
        for (int i = 0; i < n; i++) {
            scanf("%lld %lld", &x[i], &w[i]);
        }
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = INF;
            }
        }
        a[0] = 0;
        s[0] = 0;
        for (int i = 0; i < n; i++) {
            a[i + 1] = a[i] - w[i];
        }
        for (int i = 0; i < n; i++) {
            s[i + 1] = s[i] + w[i] * x[i];
        }
        dp[0][0] = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (dp[i - 1][j] != INF) {
                    dp[i - 1][j] += s[j];
                }
            }
            for (int j = i, k = i - 1; j <= n; j++) {
                while (k < j && dp[i - 1][k] != INF) {
                    point now = point(a[k], dp[i - 1][k]);
                    while (hull.size() > 1 && ((hull.back() - hull[hull.size() - 2]) ^ (now - hull.back())) >= 0) {
                        hull.pop_back();
                    }
                    k++;
                    hull.push_back(now);
                }
                int low = 0;
                int high = hull.size() - 1;
                while (high - low >= 6) {
                    int rl = low + (high - low) / 3;
                    int rr = high - (high - low) / 3;
                    long long u = hull[rl].x * x[j - 1] + hull[rl].y;
                    long long v = hull[rr].x * x[j - 1] + hull[rr].y;
                    if (u > v) {
                        low = rl;
                    } else {
                        high = rr;
                    }
                }
                for (int l = low; l <= high; l++) {
                    dp[i][j] = min(dp[i][j], hull[l].x * x[j - 1] + hull[l].y);
                }
                dp[i][j] -= a[j] * x[j - 1] + s[j];
            }
            hull.clear();
        }
        printf("%lld\n", dp[m][n]);
    }

    return 0;

}
