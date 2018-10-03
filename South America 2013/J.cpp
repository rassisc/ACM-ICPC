#include <queue>
#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 50000;

int n[2], u, v, d[N], s[N], a[2][N];
queue <int> q;
vector <int> g[2][N];

int bfs(int id, int start) {
    for (int i = 0; i < n[id]; i++) {
        d[i] = -1;
    }
    d[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        a[id][now] = max(a[id][now], d[now]);
        for (int i = 0; i < g[id][now].size(); i++) {
            int tmp = g[id][now][i];
            if (d[tmp] == -1) {
                d[tmp] = d[now] + 1;
                q.push(tmp);
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n[id]; i++) {
        if (d[i] > d[res]) {
            res = i;
        }
    }
    return res;
}

int main() {

    scanf("%d %d", &n[0], &n[1]);

    for (int i = 0; i < 2; i++) {
        for (int j = 1; j < n[i]; j++) {
            scanf("%d %d", &u, &v);
            u--;
            v--;
            g[i][u].push_back(v);
            g[i][v].push_back(u);
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n[i]; j++) {
            a[i][j] = 0;
        }
    }

    for (int i = 0; i < 2; i++) {
        int now = 0;
        for (int j = 0; j < 3; j++) {
            int tmp = bfs(i, now);
            now = tmp;
        }
    }

    for (int i = 0; i < 2; i++) {
        sort(a[i], a[i] + n[i]);
    }

    s[n[1]] = 0;

    for (int i = n[1] - 1; i >= 0; i--) {
        s[i] = s[i + 1] + a[1][i] + 1;
    }

    int A = *max_element(a[0], a[0] + n[0]);
    int B = *max_element(a[1], a[1] + n[1]);
    long long ans = 0;

    for (int i = 0; i < n[0]; i++) {
        int low = 0;
        int high = n[1] - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            int sum = a[0][i] + 1 + a[1][mid];
            if (sum <= max(A, B)) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        ans += 1LL * low * max(A, B) + s[low] + 1LL * (n[1] - low) * a[0][i];
    }

    printf("%.3f\n", 1.0 * ans / (n[0] * n[1]));

    return 0;

}
