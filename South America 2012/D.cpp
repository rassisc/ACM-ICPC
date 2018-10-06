#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int l, r, s[5010];

int main() {

    s[0] = 0;

    for (int i = 1; i <= 5000; i++) {
        s[i] = s[i - 1];
        int x = i;
        vector <int> a;
        while (x > 0) {
            a.push_back(x % 10);
            x /= 10;
        }
        int n = a.size();
        sort(a.begin(), a.end());
        a.resize(unique(a.begin(), a.end()) - a.begin());
        if (n == a.size()) {
            s[i]++;
        }
    }

    for (int t = 1; scanf("%d %d", &l, &r) != EOF; t++) {
        printf("%d\n", s[r] - s[l - 1]);
    }

    return 0;

}
