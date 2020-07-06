#include "../l/lib.h"

class APoweredAddition {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<int> A(N); cin >> A;
            int mx = -1000000000;
            int ans = 0;
            for (int i = 0; i < N; ++i) {
                ans = max(ans, mx-A[i]);
                mx = max(mx, A[i]);
            }
            for (int j = 0; j < 40; ++j) {
                if (ans < (1LL<<j)) {
                    cout << j << '\n';
                    break;
                }
            }

        }
    }
};
