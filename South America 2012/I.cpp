#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100010;

int n, m, x, l, r, a[N], tree[4 * N];
char op;

void build(int root, int rl, int rr) {
    if (rl == rr) {
        tree[root] = a[rl];
    } else {
        int rm = (rl + rr) / 2;
        build(root * 2 + 1, rl, rm);
        build(root * 2 + 2, rm + 1, rr);
        tree[root] = tree[root * 2 + 1] * tree[root * 2 + 2];
    }
}

void update(int root, int rl, int rr, int k, int v) {
    if (rl == rr) {
        tree[root] = v;
    } else {
        int rm = (rl + rr) / 2;
        if (k <= rm) {
            update(root * 2 + 1, rl, rm, k, v);
        } else {
            update(root * 2 + 2, rm + 1, rr, k, v);
        }
        tree[root] = tree[root * 2 + 1] * tree[root * 2 + 2];
    }
}

int ask(int root, int rl, int rr, int l, int r) {
    if (l > r) {
        return 1;
    }
    if (l == rl && r == rr) {
        return tree[root];
    }
    int rm = (rl + rr) / 2;
    return ask(root * 2 + 1, rl, rm, l, min(r, rm)) * ask(root * 2 + 2, rm + 1, rr, max(l, rm + 1), r);
}

int main() {

    for (int t = 1; scanf("%d %d", &n, &m) != EOF; t++) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            if (x == 0) {
                a[i] = 0;
            } else if (x < 0) {
                a[i] = -1;
            } else {
                a[i] = 1;
            }
        }
        build(0, 0, n - 1);
        for (int i = 0; i < m; i++) {
            scanf(" %c %d %d", &op, &l, &r);
            if (op == 'C') {
                l--;
                if (r == 0) {
                    update(0, 0, n - 1, l, 0);
                } else if (r > 0) {
                    update(0, 0, n - 1, l, 1);
                } else {
                    update(0, 0, n - 1, l, -1);
                }
            } else if (op == 'P') {
                l--;
                r--;
                int v = ask(0, 0, n - 1, l, r);
                if (v == 0) {
                    printf("0");
                } else if (v > 0) {
                    printf("+");
                } else {
                    printf("-");
                }
            }
        }
        puts("");
    }

    return 0;

}
