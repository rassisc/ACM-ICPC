#include <cstdio>

using namespace std;

int x, y;

int main() {

    scanf("%d", &x);

    int ans = 0;

    for (int i = 0; i < 5; i++) {
        scanf("%d", &y);
        if (x == y) {
            ans++;
        }
    }

    printf("%d\n", ans);

    return 0;

}
