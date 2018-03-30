#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10010;
const int L = 2100000;

int n, len[L], link[L], d[L], dp[L], ch[L][27];
char s[N][1010];
bool terminal[L];
vector <int> o;
vector <int> g[L];

void extend(int c, int m, int &id, int &last) {
    len[++id] = m;
    memset(ch[id], 0, sizeof ch[id]);
    int p = last;
    while (p != -1 && ch[p][c] == 0) {
        ch[p][c] = id;
        p = link[p];
    }
    last = id;
    if (p == -1) {
        link[last] = 0;
    } else if (len[ch[p][c]] == len[p] + 1) {
        link[last] = ch[p][c];
    } else {
        int t = ch[p][c];
        len[++id] = len[p] + 1;
        for (int i = 0; i < 27; i++) {
            ch[id][i] = ch[t][i];
        }
        link[id] = link[t];
        link[last] = link[t] = id;
        while (p != -1 && ch[p][c] == t) {
            ch[p][c] = id;
            p = link[p];
        }
    }
}

int main() {

    for (int t = 1; scanf("%d", &n) != EOF; t++) {
        if (n == 0) {
            break;
        }
        int id = 0;
        int now = 0;
        int last = 0;
        len[0] = 0;
        link[0] = -1;
        memset(ch[0], 0, sizeof ch[0]);
        for (int i = 0; i < n; i++) {
            scanf("%s", s[i]);
            int m = strlen(s[i]);
            if (i != 0) {
                extend(26, ++now, id, last);
            }
            for (int j = 0; j < m; j++) {
                extend(s[i][j] - 'a', ++now, id, last);
            }
        }
        for (int i = 0; i <= id; i++) {
            d[i] = 0;
            dp[i] = 0;
            terminal[i] = false;
        }
        for (int i = 0; i < n; i++) {
            int m = strlen(s[i]);
            int cur = 0;
            for (int j = 0; j < m; j++) {
                int c = s[i][j] - 'a';
                cur = ch[cur][c];
            }
            terminal[cur] = true;
        }
        for (int i = 0; i <= id; i++) {
            if (link[i] != -1) {
                d[i]++;
                g[link[i]].push_back(i);
            }
            for (int j = 0; j < 26; j++) {
                if (ch[i][j] != 0) {
                    d[ch[i][j]]++;
                }
            }
        }
        for (int i = 0; i <= id; i++) {
            if (d[i] == 0) {
                o.push_back(i);
            }
        }
        for (int i = 0; i < o.size(); i++) {
            int now = o[i];
            if (terminal[now]) {
                dp[now]++;
            }
            for (int j = 0; j < g[now].size(); j++) {
                int tmp = g[now][j];
                dp[tmp] = max(dp[tmp], dp[now]);
                if (--d[tmp] == 0) {
                    o.push_back(tmp);
                }
            }
            for (int j = 0; j < 26; j++) {
                if (ch[now][j] != 0) {
                    int tmp = ch[now][j];
                    dp[tmp] = max(dp[tmp], dp[now]);
                    if (--d[tmp] == 0) {
                        o.push_back(tmp);
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i <= id; i++) {
            ans = max(ans, dp[i]);
        }
        printf("%d\n", ans);
        o.clear();
        for (int i = 0; i <= id; i++) {
            g[i].clear();
        }
    }

    return 0;

}
