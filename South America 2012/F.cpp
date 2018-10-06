#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1000;

int n, dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
bool mark[N][N], wall[N][N][4];
char str[N];
vector < pair <int, int> > q;

string read() {
    scanf("%s", str);
    return str;
}

int main() {

    for (int t = 1; scanf("%d", &n) != EOF; t++) {
        int r = 2 * n;
        int c = 2 * n + 1;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                mark[i][j] = false;
                for (int k = 0; k < 4; k++) {
                    wall[i][j][k] = false;
                }
            }
        }
        for (int i = 0; i < 2 * n - 1; i++) {
            string s = read();
            for (int j = 0; j < n; j++) {
                int col = 2 * j + (i % 2);
                if (s[j] == 'V') {
                    wall[i][col][3] = true;
                    wall[i][col + 1][1] = true;
                    wall[i + 1][col][3] = true;
                    wall[i + 1][col + 1][1] = true;
                } else if (s[j] == 'H') {
                    wall[i][col][2] = true;
                    wall[i + 1][col][0] = true;
                    wall[i][col + 1][2] = true;
                    wall[i + 1][col + 1][0] = true;
                }
            }
        }
        int res = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (mark[i][j]) {
                    continue;
                }
                q.push_back({i, j});
                for (int p = 0; p < q.size(); p++) {
                    int x = q[p].first;
                    int y = q[p].second;
                    for (int k = 0; k < 4; k++) {
                        int nx = x + dx[k];
                        int ny = y + dy[k];
                        if (x < 0 || x >= r || y < 0 || y >= c || wall[x][y][k]) {
                            continue;
                        }
                        if (!mark[nx][ny]) {
                            mark[nx][ny] = true;
                            q.push_back({nx, ny});
                        }
                    }
                }
                res++;
                q.clear();
            }
        }
        printf("%d\n", res - 1);
    }

    return 0;

}
