#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int n, g, x, y;
vector <int> v;

int main() {

    scanf("%d %d", &n, &g);

    int ans = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        if (x > y) {
            ans += 3;
        } else if (x == y) {
            if (g > 0) {
                g--;
                ans += 3;
            } else {
                ans++;
            }
        } else {
            v.push_back(y - x);
        }
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++) {
        if (v[i] < g) {
            ans += 3;
            g -= v[i] + 1;
        } else if (v[i] == g) {
            ans++;
            g -= v[i];
            break;
        }
    }

    printf("%d\n", ans);

    return 0;

}
