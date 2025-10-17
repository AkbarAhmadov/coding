/*
    Run this code here: https://www.onlinegdb.com/online_c++_compiler
    And select "Text" input.
*/
#include <bits/stdc++.h>
#define GOOD_LUCK ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
#define endl "\n"
#define ff first
#define ss second
#define pb push_back
#define all(v) v.begin(), v.end()
using namespace std;

constexpr int MAX = 2e+5 + 1, INF = 2e+16, MOD = 1e+9 + 7, K = 31;

signed main() {

    GOOD_LUCK

    string a;
    vector <string> x;
    while (getline(cin, a)) {
        string b = "";
        b += '"';
        int cnt=0;
        for (int i=0; i < a.size(); i++) {
            if (a[i] == ' ') {
                cnt++;
                if (cnt == 4) {
                    b += "\\";
                    b += 't';
                    cnt = 0;
                }
            }
            else {
                if (cnt < 4) {
                    for (int j=0; j < cnt; j++) b += ' ';
                }
                cnt = 0;
                b += a[i];
            }
        }
        b += '"';
        b += ',';
        cout << b << endl;
    }
}
