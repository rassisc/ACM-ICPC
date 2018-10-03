#include <set>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100010;
const int INF = (int) 1e9;

int n, l[N], r[N], v[N], s[4 * N];
pair <int, int> q[N];

void build(int root, int rl, int rr) {
    if (rl == rr) {
        s[root] = v[rl];
    } else {
        int rm = (rl + rr) >> 1;
        build((root << 1) + 1, rl, rm);
        build((root << 1) + 2, rm + 1, rr);
        s[root] = min(s[(root << 1) + 1], s[(root << 1) + 2]);
    }
}

int ask(int root, int rl, int rr, int l, int r) {
    if (l > r) {
        return INF;
    }
    if (l == rl && r == rr) {
        return s[root];
    }
    int rm = (rl + rr) >> 1;
    return min(ask((root << 1) + 1, rl, rm, l, min(r, rm)), ask((root << 1) + 2, rm + 1, rr, max(l, rm + 1), r));
}

int main() {

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    for (int i = n - 1, j = 0; i >= 0; i--) {
        while (j != 0 && q[j - 1].first <= v[i]) {
            j--;
        }
        if (j != 0) {
            r[i] = q[j - 1].second;
        } else {
            r[i] = i;
        }
        q[j++] = {v[i], i};
    }

    for (int i = 0, j = 0; i < n; i++) {
        while (j != 0 && q[j - 1].first <= v[i]) {
            j--;
        }
        if (j != 0) {
            l[i] = q[j - 1].second;
        } else {
            l[i] = i;
        }
        q[j++] = {v[i], i};
    }

    build(0, 0, n - 1);

    vector <int> ans;

    for (int i = 0; i < n; i++) {
        int val = 0;
        if (l[i] != i) {
            val = max(val, ask(0, 0, n - 1, l[i], i));
        }
        if (r[i] != i) {
            val = max(val, ask(0, 0, n - 1, i, r[i]));
        }
        if (v[i] - val >= 150000) {
            ans.push_back(i + 1);
        }
    }

    for (int i = 0; i < ans.size(); i++) {
        printf("%d%c", ans[i], (i + 1 == ans.size()) ? '\n' : ' ');
    }

    return 0;

}
