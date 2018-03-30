#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100;

struct node {
    int x1;
    int y1;
    int y2;
    int val;

    node(int _x1 = 0, int _y1 = 0, int _y2 = 0, int _val = 0) {
        x1 = _x1;
        y1 = _y1;
        y2 = _y2;
        val = _val;
    }

    bool operator < (const node &rhs) const {
        if (x1 != rhs.x1) {
            return x1 < rhs.x1;
        } else if (y1 != rhs.y1) {
            return y1 < rhs.y1;
        } else if (y2 != rhs.y2) {
            return y2 < rhs.y2;
        } else {
            return val < rhs.val;
        }
    }

    bool operator == (const node &rhs) const {
        return x1 == rhs.x1 && y1 == rhs.y1 && y2 == rhs.y2 && val == rhs.val;
    }
};

int n, m, k, q, x[N], y[N];
long long pos;

void update(int y1, int y2, int val, vector < pair <int, int> > &active) {
    if (val == 1) {
        active.push_back({y1, y2});
    } else {
        int id = -1;
        vector < pair <int, int> > tmp;
        for (int i = 0; i < active.size(); i++) {
            if (active[i].first == y1 && active[i].second == y2) {
                id = i;
                break;
            }
        }
        for (int i = 0; i < active.size(); i++) {
            if (i != id) {
                tmp.push_back(active[i]);
            }
        }
        active = tmp;
    }
}

int get(vector < pair <int, int> > &active) {
    int ret = 0;
    sort(active.begin(), active.end());
    for (int i = 0; i < active.size();) {
        int j = i;
        int l = active[i].second;
        while (j < active.size() && active[j].first <= l) {
            l = max(l, active[j].second);
            j++;
        }
        ret += l - active[i].first + 1;
        i = j;
    }
    return ret;
}

long long calc(int dist, int from, int to, int col) {
    if (dist < 0) {
        return 0LL;
    }
    vector <int> o;
    vector <node> r;
    vector < pair <int, int> > active;
    for (int i = 0; i < k; i++) {
        int x1 = max(from, x[i] - dist);
        int y1 = max(0, y[i] - dist);
        int x2 = min(to, x[i] + dist);
        int y2 = min(col, y[i] + dist);
        if (x1 > x2 || y1 > y2) {
            continue;
        }
        o.push_back(x1 - 1);
        o.push_back(x1);
        o.push_back(x2);
        o.push_back(x2 + 1);
        r.push_back(node(x1, y1, y2, 1));
        r.push_back(node(x2 + 1, y1, y2, -1));
    }
    o.push_back(to);
    sort(o.begin(), o.end());
    sort(r.begin(), r.end());
    o.resize(unique(o.begin(), o.end()) - o.begin());
    int last = o[0];
    long long ret = 0;
    for (int i = 0, j = 0; i < o.size() && o[i] <= to; i++) {
        while (j < r.size() && r[j].x1 == o[i]) {
            update(r[j].y1, r[j].y2, r[j].val, active);
            j++;
        }
        long long tmp = get(active);
        ret += tmp * (o[i] - last + 1);
        last = o[i] + 1;
    }
    return ret;
}

int main() {

    for (int t = 1; scanf("%d %d %d", &n, &m, &k) != EOF; t++) {
        if (n + m + k == 0) {
            break;
        }
        for (int i = 0; i < k; i++) {
            scanf("%d %d", &x[i], &y[i]);
            x[i]--;
            y[i]--;
        }
        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            scanf("%lld", &pos);
            pos += k;
            int low = 0;
            int high = max(n, m);
            while (low <= high) {
                int mid = (low + high) / 2;
                if (calc(mid, 0, n - 1, m - 1) < pos) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            int dist = low;
            low = 0;
            high = n - 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                long long now = calc(dist, 0, mid, m - 1) + calc(dist - 1, mid + 1, n - 1, m - 1);
                if (now < pos) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            int row = low;
            low = 0;
            high = m - 1;
            long long tmp = calc(dist, 0, row - 1, m - 1) + calc(dist - 1, row, n - 1, m - 1);
            while (low <= high) {
                int mid = (low + high) / 2;
                long long now = calc(dist, row, row, mid) - calc(dist - 1, row, row, mid);
                if (now + tmp < pos) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            int col = low;
            printf("%d %d\n", row + 1, col + 1);
        }
        puts("-");
    }

    return 0;

}
