#include "../../../l/lib.h"
#include "../../../l/mod.h"

typedef Field<998244353> FF;

class DYetAnotherProblemOnASubsequence {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector2<FF> D(N+1, N+1,0);
        D[0][0] = 1;
        for (int i = 0; i < N; ++i) {
            D[i+1][0] += D[i][0];
            if (A[i] < N && A[i] > 0) {
                D[i+1][A[i]] += D[i][0];
            }
            for (int j = 1; j <= N; ++j) {
                D[i+1][j] += D[i][j];
                D[i+1][j-1] += D[i][j];
            }
        }
        cout << D[N][0]-1 << '\n';
    }
};
