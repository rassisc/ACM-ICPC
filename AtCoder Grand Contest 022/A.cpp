#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

char s[50];

int main() {

    scanf("%s", s);

    string a = s;

    if (a.size() < 26) {
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (count(a.begin(), a.end(), ch) == 0) {
                printf("%s%c\n", a.c_str(), ch);
                break;
            }
        }
    } else {
        for (int i = 25; i >= 0; i--) {
            string now = "";
            for (int j = 0; j < i; j++) {
                now += a[j];
            }
            for (char ch = 'a'; ch <= 'z'; ch++) {
                if (ch > a[i] && count(now.begin(), now.end(), ch) == 0) {
                    printf("%s%c\n", now.c_str(), ch);
                    exit(0);
                }
            }
        }
        puts("-1");
    }

    return 0;

}
