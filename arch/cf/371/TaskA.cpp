#include "../l/lib.h"
// #include "../l/mod.h"

class TaskA {
public:
void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    map<string, int> C;
    for (int t = 0; t < T; ++t) {
        char c; string S; cin >> c >> S;
        S = string(62 - S.size(), '0') + S;
        if (c == '?') {
            cout << C[S] << '\n';
        } else {
            for (char &s: S) s = '0' + (s%2);
            if (c == '+') C[S]++; else C[S]--;
        }
    }
}
};
