#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5000;

int T, n, m;
long long B, M[N], S[N], P[N], a[N];

bool check(long long res) {
    for (int i = 0; i < m; i++) {
        a[i] = min(M[i], max(0LL, res - P[i]) / S[i]);
    }
    sort(a, a + m);
    reverse(a, a + m);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += min(B, a[i]);
    }
    return sum >= B;
}

int main() {

    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d %lld %d", &n, &B, &m);
        for (int i = 0; i < m; i++) {
            scanf("%lld %lld %lld", &M[i], &S[i], &P[i]);
        }
        long long low = 0;
        long long high = (long long) (1e18 + 2e9);
        while (low <= high) {
            long long mid = (low + high) / 2;
            if (check(mid)) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        printf("Case #%d: %lld\n", t, low);
    }

    return 0;

}
