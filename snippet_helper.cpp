/*
    Run this code in your IDE with using "input.txt".
    Or you can run it on here: "https://www.onlinegdb.com/online_c++_compiler". But you need to select text input type and delete freopens(24 and 25-th lines).
    
    Also you must change the name, prefix and description in 19-th line. Remove ???-s and write whatever you want.
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

string NAME = "???", PREFIX = "???", DESC = "???";

signed main() {

    GOOD_LUCK
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cout << '"' << NAME << '"' << ": {\n";
    cout << "\t" << '"' << "prefix" << '"' << ": " << '"' << PREFIX << '"' << ",\n";
    cout << "\t" << '"' << "body" << '"' << ": [\n";

    string a;
    vector <string> x;
    while (getline(cin, a)) {
        string b = "";
        b += '"';
        int cnt=0;
        for (char &i : a) {
            if (i == 9) {
                b += "\\";
                b += 't';
            }
            else if (i == ' ') {
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
                b += i;
            }
        }
        b += '"';
        b += ',';
        cout << "\t\t" << b << endl;
    }
    cout << "\t],\n";
    cout << "\t" << '"' << "description" << '"' << ": " << '"' << DESC << '"' << ",\n";
    cout << "},";
}
