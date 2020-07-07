#include "../../../l/lib.h"

class DEqualizeTheRemainders {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N); cin >> A;
        set<int> X;
        for (int i = 0; i < M; ++i) X.insert(i);
        vector<int> C(M, 0);
        ll ans = 0;
        vector<int> B(N);
        for (int i = 0; i < N; ++i) {
            auto it = X.lower_bound(A[i]%M);
            if (it != X.end()) {
                int j = *it;
                int inc = j-A[i]%M;
                ans += inc;
                B[i] = A[i] + inc;
                if (++C[j] == N/M) X.erase(j);
            } else {
                it = X.begin();
                int j = *it;

                int inc = M+j-A[i]%M;
                ans += inc;
                B[i] = A[i] + inc;
                if (++C[j] == N/M) X.erase(j);
            }
        }
        cout << ans << '\n' << B;
    }
};
