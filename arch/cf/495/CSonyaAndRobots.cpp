#include "../../../l/lib.h"

class CSonyaAndRobots {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<int> L(N);
        set<int> S, T;
        for (int i = 0; i < N; ++i) {
            S.insert(A[i]);
            L[i] = S.size();
        }

        ll ans = 0;
        for (int i = N-1; i > 0; --i) {
            if (T.count(A[i]) == 0) {
                ans += L[i-1];
                T.insert(A[i]);
            }
        }
        cout << ans << '\n';

    }
};
