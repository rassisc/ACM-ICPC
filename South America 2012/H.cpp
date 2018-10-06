#include <cstdio>
#include <algorithm>

using namespace std;

int n;

int main() {

    for (int t = 1; scanf("%d", &n) != EOF; t++) {
        if (n % 6 == 0) {
            puts("Y");
        } else {
            puts("N");
        }
    }

    return 0;

}
