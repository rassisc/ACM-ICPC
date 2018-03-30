#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int a, b;
long long d[20][2], w[20][2];

long long calc(int to, int dig) {
    if (to == 0) {
        return 0LL;
    }
    string s = "";
    while (to > 0) {
        s += (char) (to % 10 + '0');
        to /= 10;
    }
    reverse(s.begin(), s.end());
    for (int i = 0; i <= s.size(); i++) {
        for (int j = 0; j < 2; j++) {
            d[i][j] = 0;
            w[i][j] = 0;
        }
    }
    for (int i = 1; i <= s.size(); i++) {
        for (int j = 1; j <= 9; j++) {
            if (i != 1 || j < s[0] - '0') {
                w[i][0]++;
                if (j == dig) {
                    d[i][0]++;
                }
            } else if (j == s[0] - '0') {
                w[i][1]++;
                if (j == dig) {
                    d[i][1]++;
                }
            }
        }
    }
    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < 2; j++) {
            if (j == 0) {
                d[i + 1][j] += 10LL * d[i][j];
                d[i + 1][j] += w[i][j];
                w[i + 1][j] += 10LL * w[i][j];
            } else {
                for (int k = 0; k < 10; k++) {
                    if (k < s[i] - '0') {
                        d[i + 1][0] += d[i][j];
                        w[i + 1][0] += w[i][j];
                        if (k == dig) {
                            d[i + 1][0] += w[i][j];
                        }
                    } else if (k == s[i] - '0') {
                        d[i + 1][1] += d[i][j];
                        w[i + 1][1] += w[i][j];
                        if (k == dig) {
                            d[i + 1][1] += w[i][j];
                        }
                    }
                }
            }
        }
    }
    return d[s.size()][0] + d[s.size()][1];
}

int main() {

    for (int t = 1; scanf("%d %d", &a, &b) != EOF; t++) {
        if (a + b == 0) {
            break;
        }
        for (int i = 0; i <= 9; i++) {
            printf("%lld%c", calc(b, i) - calc(a - 1, i), (i == 9) ? '\n' : ' ');
        }
    }

    return 0;

}
