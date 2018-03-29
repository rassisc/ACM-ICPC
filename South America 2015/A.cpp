#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

char u[50];

int main() {

    scanf("%s", u);

    string s = u;

    if (s.size() == 1) {
        printf("%s\n", s.c_str());
    } else {
        string a = "";
        for (char c = '9'; a.size() + 2 <= s.size(); c--) {
            a += c;
            a += c;
        }
        if (a.size() == s.size()) {
            a.pop_back();
        }
        for (int i = s.size() - 1; i >= 0; i--) {
            string v = "";
            vector <int> c(10, 0);
            for (int j = 0; j <= i; j++) {
                v += s[j];
                c[s[j] - '0']++;
            }
            if (*max_element(c.begin(), c.end()) > 2) {
                continue;
            }
            if (v.size() == s.size()) {
                a = v;
                break;
            }
            for (int ch = s[i + 1] - '1'; ch >= 0; ch--) {
                if (c[ch] != 2) {
                    c[ch]++;
                    v += (char) ('0' + ch);
                    break;
                }
            }
            if (v.size() != i + 2) {
                continue;
            }
            while (v.size() < s.size()) {
                for (int ch = 9; ch >= 0; ch--) {
                    if (c[ch] != 2) {
                        c[ch]++;
                        v += (char) ('0' + ch);
                        break;
                    }
                }
            }
            a = v;
            break;
        }
        printf("%s\n", a.c_str());
    }

    return 0;

}
