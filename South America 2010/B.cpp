#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 200;

int n, m, a[N];

int main() {

    for (int t = 1; scanf("%d %d", &n, &m) != EOF; t++) {
        if (n + m == 0) {
            break;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &a[i]);
        }
        vector <int> c(n + 1, 0);
        for (int i = 0; i < m; i++) {
            c[a[i]] = 1;
            for (int j = i + 1; j < m; j++) {
                int v = abs(a[i] - a[j]);
                c[v] = 1;
            }
        }
        int ans = 0;
        for (int i = 0; i < c.size(); i++) {
            ans += c[i];
        }
        puts(ans == n + 1 ? "Y" : "N");
    }

    return 0;

}
