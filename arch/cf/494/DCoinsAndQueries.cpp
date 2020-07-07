#include "../../../l/lib.h"

class DCoinsAndQueries {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<int> A(N); cin >> A;
        vector<int> C(31, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j <= 30; ++j) {
                C[j] += (A[i] == (1<<j));
            }
        }

        for (int i = 0; i < Q; ++i) {
            int b; cin >> b;
            int c = 0;
            for (int j = 30; j >= 0; --j) {
                int d = min(C[j], b>>j);
                c += d;
                b -= d<<j;
            }
            cout << (b==0?c:-1) << '\n';
        }
    }
};
