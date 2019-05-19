#include "../l/lib.h"
#include "../l/mod.h"

class DSashaAndInterestingFactFromGraphTheory {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, A, B; cin >> N >> M >> A >> B;
        auto F = FieldMod::fact(N+M);
        auto I = FieldMod::invfact(N+M);
        
        vector<FieldMod> PM(N+1, 1), PN(N+1, 1);
        for (int i = 0; i < N; ++i) {
            PM[i+1] = PM[i] * M;
            PN[i+1] = PN[i] * N;
        }

        FieldMod ans = 0;
        for (int l = 1; l <= N-1; ++l) {
            if (l <= M) {
                FieldMod cur = I[l-1] * I[M-l] * I[N-1-l];
                if (l != N-1) {
                    cur *= PM[N-l-1];
                    cur *= PN[N-l-2] * (l+1);
                }

                ans += cur;
            }
        }

        cout << ans * F[N-2] * F[M-1] << '\n';
    }
};
