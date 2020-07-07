#include "../../../l/lib.h"

class BInterestingSubarray {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int i = 0; i < T; ++i) {
            int N; cin >> N;
            vector<int> A(N); cin >> A;
            int ans = -1;
            for (int i = 0; i < N-1; ++i) {
                if (abs(A[i]-A[i+1]) >= 2) {
                    ans = i;
                }
            }
            if (ans == -1) {
                cout << "NO\n";
            } else {
                cout << "YES\n";
                cout << ans+1 << ' ' << ans+2 << '\n';
            }
        }
    }
};
