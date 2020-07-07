#include "../../../l/lib.h"

class CMakeGood {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<int> A(N); cin >> A;
            ll tot = 0, xr = 0;
            for (int i = 0; i < N; ++i) {
                tot += A[i];
                xr ^= A[i];
            }
            cout << 2 << '\n';
            cout << xr << ' ' << xr+tot << '\n';
        }
    }
};
