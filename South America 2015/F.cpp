#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 400010;

int n, m, x[N], y[N], f[N];
pair < pair <int, int>, int > a[N];
vector <int> c;
vector < pair < int, pair <int, int> > > e;

void add(int pos, int val) {
    while (pos < c.size()) {
        f[pos] += val;
        pos |= (pos + 1);
    }
}

int ask(int pos) {
    int ret = 0;
    while (pos >= 0) {
        ret += f[pos];
        pos = (pos & (pos + 1)) - 1;
    }
    return ret;
}

int main() {

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a[i].first.first, &a[i].first.second);
        a[i].second = i + 1;
    }

    sort(a, a + n);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    for (int i = 0; i < m; i++) {
        int j = (i + 1) % m;
        if (y[i] == y[j] && x[i] != x[j]) {
            e.push_back({min(x[i], x[j]), make_pair(y[i], 1)});
            e.push_back({max(x[i], x[j]), make_pair(y[i], -1)});
        }
    }

    for (int i = 0; i < n; i++) {
        c.push_back(a[i].first.second);
    }

    for (int i = 0; i < e.size(); i++) {
        c.push_back(e[i].second.first);
    }

    sort(c.begin(), c.end());
    sort(e.begin(), e.end());
    c.resize(unique(c.begin(), c.end()) - c.begin());

    for (int i = 0; i < c.size(); i++) {
        f[i] = 0;
    }

    long long ans = 0;

    for (int i = 0, j = 0; i < n; i++) {
        while (j < e.size() && e[j].first <= a[i].first.first) {
            int p = lower_bound(c.begin(), c.end(), e[j].second.first) - c.begin();
            add(p, e[j].second.second);
            j++;
        }
        int p = lower_bound(c.begin(), c.end(), a[i].first.second) - c.begin();
        int v = ask(p);
        if (v % 2 == 0) {
            ans += a[i].second;
        }
    }

    printf("%lld\n", ans);

    return 0;

}
