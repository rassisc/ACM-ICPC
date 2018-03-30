#include <set>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100000;

char s[N];
set <char> a;

int main() {

    for (int t = 1; gets(s); t++) {
        if (strcmp(s, "*") == 0) {
            break;
        }
        int n = strlen(s);
        for (int i = 0; i < n;) {
            if (s[i] == ' ') {
                i++;
            } else {
                a.insert(tolower(s[i]));
                while (i < n && s[i] != ' ') {
                    ++i;
                }
            }
        }
        puts(a.size() == 1 ? "Y" : "N");
        a.clear();
    }

    return 0;

}
