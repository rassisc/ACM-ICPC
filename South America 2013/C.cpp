#include <cstdio>
#include <algorithm>

using namespace std;

long long a, b, c[70], v[70];

long long calc(long long x) {
    for (int i = 0; i < 54; i++) {
        if ((x & (1LL << i)) == 0) {
            v[i + 1] = 0;
        } else {
            v[i + 1] = 1;
        }
    }
    int m = 0;
    long long ret = 0;
    for (int i = 54; i >= 1; i--) {
        if (v[i] == 1) {
            ret += c[i - 1] + m * 1LL * (1LL << (i - 1));
            m++;
        }
    }
    return ret + m;
}

int main() {

    c[0] = 0;

    for (int i = 1; i <= 55; i++) {
        c[i] = 2LL * c[i - 1] + (1LL << (i - 1));
    }

    scanf("%lld %lld", &a, &b);

    printf("%lld\n", calc(b) - calc(a - 1));

    return 0;

}
