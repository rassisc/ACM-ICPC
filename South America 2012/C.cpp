#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1200000;

int n, c[N], trie[N][28];
char s[N];
string a[N];

int main() {

    for (int t = 1; scanf("%d", &n) != EOF; t++) {
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            a[i] = s;
        }
        c[0] = 0;
        memset(trie[0], -1, sizeof trie[0]);
        for (int i = 0, id = 1; i < n; i++) {
            int now = 0;
            for (int j = 0; j < a[i].size(); j++) {
                int ch = a[i][j] - 'a';
                if (trie[now][ch] == -1) {
                    c[now]++;
                    c[id] = 0;
                    memset(trie[id], -1, sizeof trie[id]);
                    trie[now][ch] = id++;
                }
                now = trie[now][ch];
            }
            if (trie[now][27] == -1) {
                c[now]++;
                c[id] = 0;
                memset(trie[id], -1, sizeof trie[id]);
                trie[now][27] = id++;
            }
        }
        int ans = n;
        for (int i = 0; i < n; i++) {
            int now = trie[0][a[i][0] - 'a'];
            for (int j = 1; j < a[i].size(); j++) {
                if (c[now] > 1) {
                    ans++;
                }
                now = trie[now][a[i][j] - 'a'];
            }
        }
        printf("%.2f\n", 1.0 * ans / n);
    }

    return 0;

}
