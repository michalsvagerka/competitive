#include "../../../l/lib.h"
// #include "../l/mod.h"

class postupky {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> P(N); cin >> P;
        ll ans = P[0];
        for (int i = 1; i < N; ++i) {
            ans += max(0, P[i] - P[i-1]);
        }
        cout << ans << endl;
    }
};
