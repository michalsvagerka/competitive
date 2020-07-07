#include "../../../l/lib.h"
#include "../../../l/fenwick.h"

class E2MedianOnSegmentsGeneralCaseEdition {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N); cin >> A;
        auto solve = [&](vector<int> A, int M) {
            for (int &a: A) a = (a >= M) - (a < M);

            vector<int> B(N+1, 0);
            for (int i = 0; i < N; ++i) {
                B[i+1] = B[i] + (A[i]==1) - (A[i]!=1);
            }
            ll ans = 0;
            Fenwick<int> F(2*N+1, 0);
            for (int l = 0; l < N; ++l) {
                F.add(B[l] + N, 1);
                ans += F.range(B[l+1] + N, 2*N);
            }
            return ans;
        };
        cout << solve(A, M+1)-solve(A, M) << '\n';
    }
};
