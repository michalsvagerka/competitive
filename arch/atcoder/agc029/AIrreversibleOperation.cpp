#include "../l/lib.h"
// #include "../l/mod.h"

class AIrreversibleOperation {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        ll ans = 0;
        int b = 0;
        for (int i = 0; i < N; ++i) {
            if (S[i] == 'B') ++b;
            else ans += b;
        }
        cout << ans << '\n';
    }
};
