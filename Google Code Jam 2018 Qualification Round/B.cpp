#include <cstdio>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

int T, n, x;
vector <int> a;
vector <int> b;
vector <int> c;

int main() {

    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            if (i % 2 == 0) {
                a.push_back(x);
            } else {
                b.push_back(x);
            }
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        for (int i = 0, j = 0, k = 0; i < n; i++) {
            if (i % 2 == 0) {
                c.push_back(a[j++]);
            } else {
                c.push_back(b[k++]);
            }
        }
        int at = n;
        for (int i = 0; i + 1 < n; i++) {
            if (c[i] > c[i + 1]) {
                at = i;
                break;
            }
        }
        if (at == n) {
            printf("Case #%d: OK\n", t);
        } else {
            printf("Case #%d: %d\n", t, at);
        }
        a.clear();
        b.clear();
        c.clear();
    }

    return 0;

}
