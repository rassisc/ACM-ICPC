#include <cmath>
#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000;

int T, n, P, W[N], H[N];

double dist(double x1, double y1, double x2, double y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

pair <double, double> calc(int at) {
    double y1 = 0.0;
    double y2 = H[at];
    double delta = H[at] * 0.001;
    pair <double, double> ret = make_pair(1e9, -1e9);
    for (int it = 0; it < 1000; it++) {
        double now = dist(0.0, y1, W[at], y2);
        ret.first = min(ret.first, now);
        ret.second = max(ret.second, now);
        y1 += delta;
        y2 -= delta;
    }
    double x1 = 0.0;
    double x2 = W[at];
    delta = W[at] * 0.001;
    for (int it = 0; it < 1000; it++) {
        double now = dist(x1, 0.0, x2, H[at]);
        ret.first = min(ret.first, now);
        ret.second = max(ret.second, now);
        x1 += delta;
        x2 -= delta;
    }
    ret.first = sqrt(ret.first);
    ret.second = sqrt(ret.second);
    return ret;
}

int main() {

    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d %d", &n, &P);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &W[i], &H[i]);
            sum += 2 * (W[i] + H[i]);
        }
        double res = sum;
        pair <double, double> now = calc(0);
        now.first *= 2.0;
        now.second *= 2.0;
        for (int i = 1; i <= n; i++) {
            double tmp = sum + now.first * i;
            if (tmp > P) {
                continue;
            }
            tmp = min(1.0 * P, sum + now.second * i);
            if (tmp > res) {
                res = tmp;
            }
        }
        printf("Case #%d: %.10f\n", t, res);
    }

    return 0;

}
