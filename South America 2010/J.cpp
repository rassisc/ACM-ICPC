#include <cstdio>
#include <algorithm>

using namespace std;

int a[5], b[5];

int main() {

    for (int t = 1; scanf("%d %d %d %d %d", &a[0], &a[1], &a[2], &b[0], &b[1]) != EOF; t++) {
        if (a[0] + a[1] + a[2] + b[0] + b[1] == 0) {
            break;
        }
        int ans = -1;
        for (int i = 1; i <= 52; i++) {
            if (i != a[0] && i != a[1] && i != a[2] && i != b[0] && i != b[1]) {
                b[2] = i;
                bool can = false;
                for (int x = 0; x < 3; x++) {
                    for (int y = 0; y < 3; y++) {
                        for (int j = 0; j < 3; j++) {
                            for (int k = 0; k < 3; k++) {
                                can |= (x != y && j != k && a[x] > b[j] && a[y] > b[k]);
                            }
                        }
                    }
                }
                if (!can) {
                    ans = i;
                    break;
                }
            }
        }
        printf("%d\n", ans);
    }

    return 0;

}
