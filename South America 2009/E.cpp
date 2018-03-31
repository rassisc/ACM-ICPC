#include <cstdio>
#include <algorithm>

using namespace std;

int A, B;

int get(int x) {
    if (x <= 100) {
        return 2 * x;
    } else if (x <= 10000) {
        return 2 * 100 + 3 * (x - 100);
    } else if (x <= 1000000) {
        return 2 * 100 + 3 * 9900 + 5 * (x - 10000);
    } else {
        return 2 * 100 + 3 * 9900 + 5 * 990000 + 7 * (x - 1000000);
    }
}

int main() {

    for (int t = 1; scanf("%d %d", &A, &B) != EOF; t++) {
        if (A + B == 0) {
            break;
        }
        int l = 1;
        int r = (int) 2e8;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (get(mid) < A) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        int low = 0;
        int high = l / 2;
        while (low <= high) {
            int mid = (low + high) / 2;
            int val = abs(get(mid) - get(l - mid));
            if (val > B) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        printf("%d\n", get(low));
    }

    return 0;

}
