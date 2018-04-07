#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 55;

int n, a[N], b[N], c[N];
bool mark[N];
vector <int> q;

bool check() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < N; j++) {
            mark[j] = false;
        }
        mark[a[i]] = true;
        q.push_back(a[i]);
        for (int j = 0; j < q.size(); j++) {
            int now = q[j];
            for (int k = 1; k < N; k++) {
                int tmp = now % k;
                if (c[k] == 1 && !mark[tmp]) {
                    mark[tmp] = true;
                    q.push_back(tmp);
                }
            }
        }
        q.clear();
        if (!mark[b[i]]) {
            return false;
        }
    }
    return true;
}

int main() {

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
    }

    for (int i = 0; i < N; i++) {
        c[i] = 1;
    }

    if (!check()) {
        puts("-1");
        exit(0);
    }

    long long res = 0;

    for (int i = N - 1; i >= 0; i--) {
        c[i] = 0;
        if (!check()) {
            c[i] = 1;
            res |= 1LL << i;
        }
    }

    printf("%lld\n", res);

    return 0;

}
