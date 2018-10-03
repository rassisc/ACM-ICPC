#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

const int N = 100;

int n, a[N];
long long m[N];
vector <long long> s[N];

int main() {

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int l = *max_element(a, a + n);
    int c = count(a, a + n, l);
    m[l] = 1;

    for (int i = 0; i < c; i++) {
        s[l].push_back(1);
    }

    for (int i = l - 1; i >= 0; i--) {
        for (int j = 0; j < s[i + 1].size(); j += 2) {
            s[i].push_back(s[i + 1][j] + s[i + 1][j + 1]);
        }
        int c = count(a, a + n, i);
        for (int j = 0; j < c; j++) {
            s[i].push_back(m[i + 1]);
        }
        sort(s[i].begin(), s[i].end());
        m[i] = s[i].back();
    }

    printf("%lld\n", m[0]);

    return 0;

}
