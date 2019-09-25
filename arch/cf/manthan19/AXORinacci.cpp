#include "../l/lib.h"

class AXORinacci {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int A, B, N; cin >> A >> B >> N;
            N %= 3;
            if (N == 0) {
                cout << A << '\n';
            } else if (N == 1) {
                cout << B << '\n';
            } else {
                cout << (A^B) << '\n';
            }
        }
    }
};
