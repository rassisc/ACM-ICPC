#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200010;

int get(char ch) {
    if ('a' <= ch && ch <= 'z') {
        return ch - 'a';
    } else if ('A' <= ch && ch <= 'Z') {
        return ch - 'A' + 26;
    } else if ('0' <= ch && ch <= '9') {
        return ch - '0' + 52;
    } else if (ch == '.') {
        return 62;
    } else if (ch == ',') {
        return 63;
    } else {
        return -1;
    }
}

struct SuffixArray {
    int x[N];
    int y[N];
    int v[N];
    int a[N];
    int sa[N];
    int buc[N];
    int rank[N];
    int height[N];

    bool cmp(int A, int B, int len) {
        return y[A] == y[B] && y[A + len] == y[B + len];
    }

    void build(string str, int m = 65) {
        int n = str.size();
        for (int i = 0; i < n; i++) {
            a[i] = get(str[i]) + 1;
        }
        a[n++] = 0;
        for (int i = 0; i < m; i++) {
            buc[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            ++buc[x[i] = a[i]];
        }
        for (int i = 1; i < m; i++) {
            buc[i] += buc[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            sa[--buc[x[i]]] = i;
        }
        for (int j = 1, p = 0; p < n; j *= 2, m = p) {
            p = 0;
            for (int i = n - j; i < n; i++) {
                y[p++] = i;
            }
            for (int i = 0; i < n; i++) {
                if (sa[i] >= j) {
                    y[p++] = sa[i] - j;
                }
            }
            for (int i = 0; i < m; i++) {
                buc[i] = 0;
            }
            for (int i = 0; i < n; i++) {
                ++buc[v[i] = x[y[i]]];
            }
            for (int i = 1; i < m; i++) {
                buc[i] += buc[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                sa[--buc[v[i]]] = y[i];
            }
            for (int i = 0; i < n; i++) {
                swap(x[i], y[i]);
            }
            p = 1;
            x[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                x[sa[i]] = cmp(sa[i], sa[i - 1], j) ? p - 1 : p++;
            }
        }
        n--;
        for (int i = 1; i <= n; i++) {
            rank[sa[i]] = i;
        }
        for (int i = 0, k = 0; i < n; height[rank[i++]] = k) {
            k = max(k - 1, 0);
            for (int j = sa[rank[i] - 1]; a[i + k] == a[j + k]; k++);
        }
    }
} SA;

char s[N];

int main() {

    for (int t = 1; scanf("%s", s) != EOF; t++) {
        if (strcmp(s, "*") == 0) {
            break;
        }
        SA.build(s);
        int n = strlen(s);
        long long res = 0;
        for (int i = 1; i <= n; i++) {
            res += max(0, SA.height[i] - SA.height[i - 1]);
        }
        printf("%lld\n", res);
    }

    return 0;

}
