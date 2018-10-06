#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int w, d, a, k, p[5][10], q[5][10];
double T[20], S[20], C[20], R[20];
pair <double, double> u[5];

double f(double x, double mid) {
    double res = 0.0;
    for (int i = 0; i < 2; i++) {
        u[i] = {0, 0};
        double r = 1.0;
        for (int j = 0; j <= k; j++) {
            u[i].first += r * p[i][j];
            u[i].second += r * q[i][j];
            r *= x;
        }
    }
    double y1 = -(u[0].first / u[0].second);
    double y2 = -(u[1].first / u[1].second);
    if (mid < y1) {
        return 0.0;
    }
    if (mid > y2) {
        return y2 - y1;
    }
    return mid - y1;
}

double calc(double mid) {
    double h = w;
    double tmp = (f(0.0, mid) + f(1.0 * w, mid)) * h * 0.5;
    T[0] = tmp;
    for (int i = 0; i < 12; i++) {
        tmp = 0;
        double x = 0.0 + h * 0.5;
        while (x < w) {
            tmp += f(x, mid);
            x += h;
        }
        T[i + 1] = (T[i] + h * tmp) * 0.5;
        h *= 0.5;
    }
    for (int i = 0; i < 12; i++) {
        S[i] = (4.0 * T[i + 1] - T[i]) / 3.0;
    }
    for (int i = 0; i < 11; i++) {
        C[i] = (16.0 * S[i + 1] - S[i]) / 15.0;
    }
    for (int i = 0; i < 10; i++) {
        R[i] = (64.0 * C[i + 1] - C[i]) / 63.0;
    }
    return R[9];
}

int main() {

    for (int t = 1; scanf("%d %d %d %d", &w, &d, &a, &k) != EOF; t++) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j <= k; j++) {
                scanf("%d", &p[i][j]);
            }
            for (int j = 0; j <= k; j++) {
                scanf("%d", &q[i][j]);
            }
        }
        double low = 0;
        double high = d;
        for (int it = 0; it < 80; it++) {
            double mid = (low + high) * 0.5;
            double now = calc(mid);
            if (now > a) {
                high = mid;
            } else {
                low = mid;
            }
        }
        printf("%.5f\n", low);
    }

    return 0;

}
