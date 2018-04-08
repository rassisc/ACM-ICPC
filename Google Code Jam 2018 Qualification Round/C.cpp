#include <ctime>
#include <cstdio>
#include <random>
#include <vector>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int T, A, x, y, a[N][N], c[N][N], d[N][N];
vector < pair < pair <int, int>, pair <int, int> > > s;

pair <int, int> get() {
    for (int i = 0; i < s.size(); i++) {
        int x = s[i].second.first;
        int y = s[i].second.second;
        s[i].first.first = c[x][y];
        s[i].first.second = d[x][y];
    }
    sort(s.begin(), s.end());
    while (s.back().first.first == 9) {
        s.pop_back();
    }
    int at = abs(rand()) % min((int) s.size(), 5);
    return s[at].second;
}

void update(int x, int y) {
    if (a[x][y] == 1) {
        return;
    }
    a[x][y] = 1;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx;
            int ny = y + dy;
            c[nx][ny]++;
        }
    }
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            int nx = x + dx;
            int ny = y + dy;
            d[nx][ny]--;
        }
    }
}

int main() {

    srand(time(NULL));

    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d", &A);
        memset(a, 0, sizeof a);
        memset(c, 0, sizeof c);
        memset(d, 0, sizeof d);
        for (int i = 434; i <= 436; i++) {
            for (int j = 802; j <= 839; j++) {
                s.push_back(make_pair(make_pair(c[i][j], d[i][j]), make_pair(i, j)));
            }
        }
        for (int it = 0; it < 1000; it++) {
            pair <int, int> now = get();
            printf("%d %d\n", now.first, now.second);
            fflush(stdout);
            scanf("%d %d", &x, &y);
            if (x == 0 && y == 0) {
                break;
            }
            update(x, y);
        }
        s.clear();
    }

    return 0;

}
