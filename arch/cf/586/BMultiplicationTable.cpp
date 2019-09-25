#include "../l/lib.h"

class BMultiplicationTable {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector2<int> A(N, N); cin >> A;
        ll asq = ll(A[0][1]) * A[0][2] / A[1][2];
        ll a = bsl(0LL, 1000000000LL, [&](ll x) { return x*x >= asq; });
        vector<int> B(N);
        B[0] = a;
        for (int i = 1; i < N; ++i) {
            B[i] = A[0][i] / a;
        }
        cout << B;
    }
};
