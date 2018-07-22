#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 400;

int T, n, a[N], c[N];
char res[N][N];
vector <int> g[N];

void put(int rows, int at, char ch) {
    for (int i = 0; i < rows; i++) {
        res[i][at] = ch;
        at += (ch == '/' ? -1 : 1);
    }
}

int main() {

    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            c[i] = 1;
        }
        if (a[0] == 0 || a[n - 1] == 0) {
            printf("Case #%d: IMPOSSIBLE\n", t);
        } else {
            int rows = 0;
            for (int i = 0; i < n; i++) {
                int x = a[i];
                for (int j = 0; j < n; j++) {
                    if (x > 0 && c[j] > 0) {
                        x--;
                        c[j]--;
                        g[i].push_back(j);
                    }
                }
                for (int j = 0; j < g[i].size(); j++) {
                    rows = max(rows, abs(i - g[i][j]) + 1);
                }
            }
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < n; j++) {
                    res[i][j] = '.';
                }
            }
            for (int i = 0; i < n; i++) {
                if (g[i].size() == 0) {
                    continue;
                }
                int from = g[i][0];
                int to = g[i][g[i].size() - 1];
                for (int j = from; j <= to; j++) {
                    if (j < i) {
                        put(i - j, j, '\\');
                    } else if (j > i) {
                        put(j - i, j, '/');
                    }
                }
            }
            printf("Case #%d: %d\n", t, rows);
            for (int i = 0; i < rows; i++) {
                res[i][n] = '\0';
                printf("%s\n", res[i]);
            }
        }
        for (int i = 0; i < n; i++) {
            g[i].clear();
        }
    }

    return 0;

}
