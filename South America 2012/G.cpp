#include <ctime>
#include <random>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100;
const int M = 3000;

int n, m, match[M], a[N][N], dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
char s[N][N];
bool mark[M];
vector <int> g[M];

bool dfs(int now) {
    if (mark[now]) {
        return false;
    }
    mark[now] = true;
    for (int i = 0; i < g[now].size(); i++) {
        int tmp = g[now][i];
        if (match[tmp] == -1 || dfs(match[tmp])) {
            match[now] = tmp;
            match[tmp] = now;
            return true;
        }
    }
    return false;
}

int main() {

    srand(time(NULL));

    for (int t = 1; scanf("%d %d", &n, &m) != EOF; t++) {
        for (int i = 0; i < n; i++) {
            scanf("%s", s[i]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i][j] = i * m + j;
            }
        }
        int sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s[i][j] == 'X') {
                    continue;
                }
                sum += ((i + j) % 2 == 0) ? 1 : -1;
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x < 0 || x >= n || y < 0 || y >= m || s[x][y] == 'X') {
                        continue;
                    }
                    if ((i + j) % 2 == 0) {
                        g[a[i][j]].push_back(a[x][y]);
                    } else {
                        g[a[x][y]].push_back(a[i][j]);
                    }
                }
            }
        }
        for (int i = 0; i < n * m; i++) {
            match[i] = -1;
            random_shuffle(g[i].begin(), g[i].end());
        }
        bool win = sum == 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if ((i + j) % 2 == 1 || s[i][j] == 'X' || match[a[i][j]] != -1) {
                    continue;
                }
                for (int k = 0; k < n * m; k++) {
                    mark[k] = false;
                }
                if (!dfs(a[i][j])) {
                    win = false;
                    break;
                }
            }
            if (!win) {
                break;
            }
        }
        puts(win ? "2" : "1");
        for (int i = 0; i < n * m; i++) {
            g[i].clear();
        }
    }

    return 0;

}
