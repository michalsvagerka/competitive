#include "../l/lib.h"
// #include "../l/mod.h"

class yinyang {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        if (N%2 == 0 && count(S.begin(),S.end(),'W') == N/2) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
};
