#include <cstdio>
#include <algorithm>

using namespace std;

const long long INF = (long long) 2e18;

int Q;
long long l, r;

long long get(long long at, long long n, bool reverse) {
    if (!reverse) {
        return at < l ? at : (at + 1);
    } else {
        return at < r ? at : (at + 1);
    }
}

long long mul(long long x, long long y) {
    if (x >= INF / y) {
        return INF;
    }
    return x * y;
}

bool check(long long res, long long score) {
    long long low = 1;
    long long high = res;
    while (high - low >= 10) {
        long long rl = low + (high - low) / 3;
        long long rr = high - (high - low) / 3;
        long long x = mul(get(rl, res, false), get(res - rl + 1, res, true));
        long long y = mul(get(rr, res, false), get(res - rr + 1, res, true));
        if (max(x, y) >= score) {
            return false;
        }
        if (x < y) {
            low = rl;
        } else {
            high = rr;
        }
    }
    for (long long now = low; now <= high; now++) {
        long long x = mul(get(now, res, false), get(res - now + 1, res, true));
        if (x >= score) {
            return false;
        }
    }
    return true;
}

int main() {

    scanf("%d", &Q);

    for (int i = 0; i < Q; i++) {
        scanf("%lld %lld", &l, &r);
        long long low = 0;
        long long high = (long long) 1e18;
        while (low <= high) {
            long long mid = (low + high) / 2;
            if (check(mid, l * r)) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        printf("%lld\n", high);
    }

    return 0;

}
