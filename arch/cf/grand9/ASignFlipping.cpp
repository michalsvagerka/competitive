#include "../l/lib.h"

class ASignFlipping {
public:
    void solve(istream& cin, ostream& cout) {
        int T;cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<int> A(N); cin >> A;
            for (int i = 0; i < N; ++i) {
                if (i%2) {
                    A[i] = -abs(A[i]);
                } else {
                    A[i] = abs(A[i]);
                }
            }
            cout << A;
        }
    }
};
