#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100010;

int n;
char x[20], y[20];
pair <int, int> a[N];

pair <int, int> get() {
    scanf("%s %s", x, y);
    int u = ((x[0] - '0') * 10 + x[1] - '0') * 3600 + ((x[3] - '0') * 10 + x[4] - '0') * 60 + (x[6] - '0') * 10 + x[7] - '0';
    int v = y[0] == 'E' ? 0 : (y[0] == 'X' ? 1 : -1);
    return make_pair(u, v);
}

int main() {

    for (int t = 1; scanf("%d", &n) != EOF; t++) {
        if (n == 0) {
            break;
        }
        for (int i = 0; i < n; i++) {
            a[i] = get();
        }
        sort(a, a + n);
        int c = 0;
        int v = 0;
        for (int i = 0; i < n; i++) {
            if (a[i].second == 0) {
                c++;
            } else if (a[i].second == 1) {
                c--;
            } else if (a[i].second == -1) {
                v++;
            }
        }
        v = max(0, -c) + (v - abs(c)) / 2;
        for (int i = 0; i < n; i++) {
            if (a[i].second == -1) {
                if (v > 0) {
                    v--;
                    a[i].second = 0;
                } else {
                    a[i].second = 1;
                }
            }
        }
        int now = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i].second == 0) {
                now++;
            } else if (a[i].second == 1) {
                now--;
            }
            ans = max(ans, now);
        }
        printf("%d\n", ans);
    }

    return 0;

}
