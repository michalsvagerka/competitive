#include "../l/lib.h"
// #include "../l/mod.h"

class CSequenceGrowingEasy {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        if (A[0]) { cout << -1 << endl; return; }
        ll ans = A.back();
        for (int i = 1; i < N; ++i) {
            if (A[i] > A[i-1]+1) { cout << -1 << endl; return; }
            if (A[i] < A[i-1]+1) ans += A[i-1];
        }
        cout << ans << '\n';
    }
};
