#include "../l/lib.h"
// #include "../l/mod.h"

class DCommonDivisors {
public:
    void solve(istream& cin, ostream& cout) {
        string S, T; cin >> S >> T;
        int A = S.size(), B = T.size();
        int ans = 0;
        for (int i = 1; i <= A; ++i) {
            if (A%i == 0 && B%i == 0) {
                bool ok = true;
                for (int j = 0; j < A && ok; ++j) ok &= S[j]==S[j%i];
                for (int j = 0; j < B && ok; ++j) ok &= T[j]==S[j%i];
                ans += ok;
            }
        }
        cout << ans << '\n';
    }
};
