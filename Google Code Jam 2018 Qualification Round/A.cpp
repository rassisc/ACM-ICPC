#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

int T, n;
char s[1000];

long long calc(string a) {
    long long p = 1;
    long long r = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == 'S') {
            r += p;
        } else {
            p += p;
        }
    }
    return r;
}

int main() {

    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d %s", &n, s);
        int m = strlen(s);
        int k = count(s, s + m, 'S');
        if (k > n) {
            printf("Case #%d: IMPOSSIBLE\n", t);
        } else {
            int res = 0;
            while (calc(s) > n) {
                for (int i = m - 2; i >= 0; i--) {
                    if (s[i] == 'C' && s[i + 1] == 'S') {
                        swap(s[i], s[i + 1]);
                        break;
                    }
                }
                ++res;
            }
            printf("Case #%d: %d\n", t, res);
        }
    }

    return 0;

}
