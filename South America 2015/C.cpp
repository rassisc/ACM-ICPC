#include <cstdio>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 300010;
const long long INF = (long long) 3e18;

int n;
long long x[N], y[N], s[N];

long long calc(int from, int to) {
    long long res = s[to] - s[from] + x[to] * y[from] - y[to] * x[from];
    return max(res, llabs(s[n]) - res);
}

int main() {

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &x[i], &y[i]);
        x[i + n] = x[i];
        y[i + n] = y[i];
    }

    s[0] = 0;

    for (int i = 0; i < 2 * n; i++) {
        s[i + 1] = s[i] + x[i] * y[i + 1] - y[i] * x[i + 1];
    }

    long long ans = -1;

    for (int i = 0; i < n; i++) {
        int low = i + 2;
        int high = i + n - 2;
        while (high - low >= 6) {
            int rl = low + (high - low) / 3;
            int rr = high - (high - low) / 3;
            if (calc(i, rl) > calc(i, rr)) {
                low = rl;
            } else {
                high = rr;
            }
        }
        long long now = INF;
        for (int j = low; j <= high; j++) {
            now = min(now, calc(i, j));
        }
        ans = max(ans, now);
    }

    printf("%lld %lld\n", ans, llabs(s[n]) - ans);

    return 0;

}
