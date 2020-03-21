#include "../l/lib.h"

class BChloeAndTheSequence {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        ll K; cin >> K;
        int ans = 1;
        while (K%2 == 0) { K /= 2; ans++; }
        cout << ans << '\n';
    }
};
