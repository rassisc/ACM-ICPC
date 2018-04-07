#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 150;

int a, b, c, d[N][N][N];
vector < pair < int, pair <int, int> > > q;

void add(int x, int y, int z, int c) {
    if (x >= N || y >= N || z >= N) {
        return;
    }
    if (d[x][y][z] == -1) {
        d[x][y][z] = c + 1;
        q.push_back(make_pair(x, make_pair(y, z)));
    }
}

int main() {

    scanf("%d %d %d", &a, &b, &c);

    memset(d, -1, sizeof d);

    d[a][b][c] = 0;
    q.push_back(make_pair(a, make_pair(b, c)));

    for (int i = 0; i < q.size(); i++) {
        int x = q[i].first;
        int y = q[i].second.first;
        int z = q[i].second.second;
        if (x == y && y == z) {
            printf("%d\n", d[x][y][z]);
            exit(0);
        }
        add(x + 1, y + 1, z, d[x][y][z]);
        add(x + 1, y, z + 1, d[x][y][z]);
        add(x, y + 1, z + 1, d[x][y][z]);
        add(x + 2, y, z, d[x][y][z]);
        add(x, y + 2, z, d[x][y][z]);
        add(x, y, z + 2, d[x][y][z]);
    }

    return 0;

}
