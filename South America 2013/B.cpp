#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100100;

struct SegmentTree {
    int m;
    int u[4 * N];
    int v[4 * N];
    bool rev[4 * N];

    void build(int root, int rl, int rr) {
        if (rl == rr) {
            u[root] = -1;
            v[root] = m + 1;
            rev[root] = false;
        } else {
            int rm = (rl + rr) / 2;
            build(root * 2 + 1, rl, rm);
            build(root * 2 + 2, rm + 1, rr);
            rev[root] = false;
            u[root] = max(u[root * 2 + 1], u[root * 2 + 2]);
            v[root] = min(v[root * 2 + 1], v[root * 2 + 2]);
        }
    }

    void down(int root) {
        if (rev[root]) {
            int x = u[root * 2 + 1];
            int y = u[root * 2 + 2];
            rev[root] = false;
            rev[root * 2 + 1] ^= true;
            rev[root * 2 + 2] ^= true;
            u[root * 2 + 1] = m - v[root * 2 + 1];
            v[root * 2 + 1] = m - x;
            u[root * 2 + 2] = m - v[root * 2 + 2];
            v[root * 2 + 2] = m - y;
        }
    }

    void update(int root, int rl, int rr, int at, int x) {
        if (rl == rr) {
            u[root] = x;
            v[root] = x;
        } else {
            int rm = (rl + rr) / 2;
            down(root);
            if (at <= rm) {
                update(root * 2 + 1, rl, rm, at, x);
            } else {
                update(root * 2 + 2, rm + 1, rr, at, x);
            }
            u[root] = max(u[root * 2 + 1], u[root * 2 + 2]);
            v[root] = min(v[root * 2 + 1], v[root * 2 + 2]);
        }
    }

    void modify(int root, int rl, int rr, int l, int r) {
        if (l > r) {
            return;
        }
        if (l <= rl && rr <= r) {
            int tmp = u[root];
            u[root] = m - v[root];
            v[root] = m - tmp;
            rev[root] ^= true;
            return;
        }
        down(root);
        int rm = (rl + rr) / 2;
        modify(root * 2 + 1, rl, rm, l, min(r, rm));
        modify(root * 2 + 2, rm + 1, rr, max(l, rm + 1), r);
        u[root] = max(u[root * 2 + 1], u[root * 2 + 2]);
        v[root] = min(v[root * 2 + 1], v[root * 2 + 2]);
    }

    int query(int root, int rl, int rr, int l, int r) {
        if (l > r) {
            return -1;
        }
        if (l == rl && r == rr) {
            return u[root];
        }
        int rm = (rl + rr) / 2;
        down(root);
        u[root] = max(u[root * 2 + 1], u[root * 2 + 2]);
        v[root] = min(v[root * 2 + 1], v[root * 2 + 2]);
        return max(query(root * 2 + 1, rl, rm, l, min(r, rm)), query(root * 2 + 2, rm + 1, rr, max(l, rm + 1), r));
    }
} seg;

struct FenwickTree {
    int len;
    int f[N];

    void init(int n) {
        len = n;
        for (int i = 0; i < n; i++) {
            f[i] = 0;
        }
    }

    void madd(int &x, int y) {
        x += y;
        if (x < 0) {
            x += 2;
        }
        if (x >= 2) {
            x -= 2;
        }
    }

    void add(int at, int val) {
        while (at < len) {
            madd(f[at], val);
            at |= (at + 1);
        }
    }

    int ask(int at) {
        int ret = 0;
        while (at >= 0) {
            madd(ret, f[at]);
            at = (at & (at + 1)) - 1;
        }
        return ret;
    }
} bit;

int q, l, r, a[N], c[N], e[15];
char s[N], p[15];
bool mark[N];

int main() {

    scanf("%d %s %s", &q, p, s);

    int n = strlen(s);
    int m = strlen(p);

    for (int i = 0; i < n; i++) {
        a[i] = -1;
        mark[i] = false;
    }

    bit.init(n);
    seg.m = m;
    seg.build(0, 0, n - 1);

    for (int i = 0; i < n; i++) {
        if ('A' <= s[i] && s[i] <= 'Z') {
            bit.add(i, 1);
            bit.add(i + 1, -1);
        }
    }

    for (int i = 0; i < m; i++) {
        if ('A' <= p[i] && p[i] <= 'Z') {
            e[i] = 1;
        } else {
            e[i] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        int j = i + m - 1;
        if (j >= n) {
            break;
        }
        bool valid = true;
        for (int k = 0; k < m; k++) {
            if (tolower(s[i + k]) != tolower(p[k])) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            continue;
        }
        a[i] = 0;
        mark[i] = true;
        for (int k = 0; k < m; k++) {
            if (s[i + k] != p[k]) {
                a[i]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (a[i] != -1) {
            seg.update(0, 0, n - 1, i, a[i]);
        }
    }

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &l, &r);
        l--;
        r--;
        int res = seg.query(0, 0, n - 1, l, r - m + 1);
        printf("%d\n", res);
        int u = max(0, l - m);
        int v = min(n - 1, r + m);
        bit.add(l, 1);
        bit.add(r + 1, -1);
        for (int j = u; j < l; j++) {
            c[j] = bit.ask(j);
        }
        for (int j = r + 1; j <= v; j++) {
            c[j] = bit.ask(j);
        }
        for (int j = l, k = 0; j <= r && k < m; j++, k++) {
            c[j] = bit.ask(j);
        }
        for (int j = r, k = 0; j >= l && k < m; j--, k++) {
            c[j] = bit.ask(j);
        }
        for (int j = u; j < l; j++) {
            if (!mark[j]) {
                continue;
            }
            int now = 0;
            for (int k = 0; k < m; k++) {
                int pos = j + k;
                if (c[pos] != e[k]) {
                    now++;
                }
            }
            a[j] = now;
            seg.update(0, 0, n - 1, j, a[j]);
        }
        for (int j = max(l, r - m + 2); j <= r; j++) {
            if (!mark[j]) {
                continue;
            }
            int now = 0;
            for (int k = 0; k < m; k++) {
                int pos = j + k;
                if (c[pos] != e[k]) {
                    now++;
                }
            }
            a[j] = now;
            seg.update(0, 0, n - 1, j, a[j]);
        }
        seg.modify(0, 0, n - 1, l, r - m + 1);
    }

    return 0;

}
