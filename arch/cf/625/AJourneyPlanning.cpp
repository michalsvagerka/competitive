#include "../l/lib.h"

class AJourneyPlanning {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        map<int,ll> X;
        for (int i = 0; i < N; ++i) {
            X[A[i]-i] += A[i];
        }
        ll ans = 0;
        for (auto x:X) ans = max(ans, x.y);
        cout << ans << '\n';
    }
};
