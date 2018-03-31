#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char s[1010];

int main() {

    for (int t = 1; scanf("%s", s) != EOF; t++) {
        if (s[0] == '*') {
            break;
        }
        int n = strlen(s);
        int ans = 0;
        for (int i = 1; i < n; i++) {
            int v = 0;
            while (s[i] != '/') {
                char ch = s[i];
                if (ch == 'W') {
                    v += 64;
                } else if (ch == 'H') {
                    v += 32;
                } else if (ch == 'Q') {
                    v += 16;
                } else if (ch == 'E') {
                    v += 8;
                } else if (ch == 'S') {
                    v += 4;
                } else if (ch == 'T') {
                    v += 2;
                } else if (ch == 'X') {
                    v += 1;
                }
                i++;
            }
            if (v == 64) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }

    return 0;

}
