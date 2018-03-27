#include "../../../l/lib.h"
// #include "../l/mod.h"

class C {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N+2, 0);
        for (int i = 1; i <= N; ++i) {
            cin >> A[i];
        }
        int tot = 0;
        for (int i = 1; i <= N+1; ++i) {
            tot += abs(A[i]-A[i-1]);
        }

        vector<int> B(N, tot);
        for (int i = 1; i <= N; ++i) {
            B[i-1] -= abs(A[i]-A[i-1]) + abs(A[i+1]-A[i]);
            B[i-1] += abs(A[i+1] - A[i-1]);
        }

        for (int i = 0; i < N; ++i) cout << B[i] << '\n';
    }
};
