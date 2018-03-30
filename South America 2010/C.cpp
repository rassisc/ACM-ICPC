#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200;
const double EPS = 1e-9;

int dcmp(double val) {
    return val > EPS ? 1 : (val < -EPS ? -1 : 0);
}

struct point {
    double x;
    double y;

    point(double _x = 0, double _y = 0) {
        x = _x;
        y = _y;
    }

    point operator + (const point &rhs) const {
        return point(x + rhs.x, y + rhs.y);
    }

    point operator - (const point &rhs) const {
        return point(x - rhs.x, y - rhs.y);
    }

    point operator * (const double &rhs) const {
        return point(x * rhs, y * rhs);
    }

    point operator / (const double &rhs) const {
        return point(x / rhs, y / rhs);
    }

    double operator ^ (const point &rhs) const {
        return x * rhs.y - rhs.x * y;
    }

    bool operator < (const point &rhs) const {
        return dcmp(x - rhs.x) < 0 || (dcmp(x - rhs.x) == 0 && dcmp(y - rhs.y) < 0);
    }

    bool operator == (const point &rhs) const {
        return dcmp(x - rhs.x) == 0 && dcmp(y - rhs.y) == 0;
    }
} p[N];

int n;

point intersection(point a, point b, point c, point d) {
    b = b - a;
    d = c - d;
    c = c - a;
    return a + b * (c ^ d) / (b ^ d);
}

point center(point a, point b, point c) {
    b = (a + b) / 2;
    c = (a + c) / 2;
    return intersection(b, b + point(a.y - b.y, b.x - a.x), c, c + point(a.y - c.y, c.x - a.x));
}

int main() {

    for (int t = 1; scanf("%d", &n) != EOF; t++) {
        if (n == 0) {
            break;
        }
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &p[i].x, &p[i].y);
        }
        int res = min(2, n);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                vector <point> v;
                for (int k = j + 1; k < n; k++) {
                    if (dcmp((p[k] - p[i]) ^ (p[k] - p[j])) == 0) {
                        continue;
                    }
                    point now = center(p[i], p[j], p[k]);
                    v.push_back(now);
                }
                sort(v.begin(), v.end());
                for (int k = 0; k < v.size();) {
                    int l = k;
                    while (l < v.size() && v[k] == v[l]) {
                        l++;
                    }
                    res = max(res, 2 + l - k);
                    k = l;
                }
            }
        }
        printf("%d\n", res);
    }

    return 0;

}
