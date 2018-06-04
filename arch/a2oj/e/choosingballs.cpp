#include "../../../l/lib.h"
// #include "../l/mod.h"

class choosingballs {
public:
    void solve(istream& cin, ostream& cout) {
        int N, Q; cin >> N >> Q;
        vector<int> V(N), C(N); cin >> V >> C;
        for (int q = 0; q < Q; ++q) {
            ll A, B; cin >> A >> B;
            pair<ll,int> m1 = {0, -1}, m2 = {0, -1};
            vector<ll> MX(N+1, -1e16);
            for (int i = 0; i < N; ++i) {
                ll best = -1e16;
                if (m1.y != C[i]) best = max(best, m1.x + V[i] * B);
                if (m2.y != C[i]) best = max(best, m2.x + V[i] * B);
                best = max(best, MX[C[i]] + V[i] * A);

                MX[C[i]] = max(MX[C[i]], best);
                if (m1.y == C[i]) {
                    m1.x = max(m1.x, best);
                } else if (best > m1.x) {
                    m2 = m1;
                    m1 = {best,C[i]};
                } else if (best > m2.x) {
                    m2 = {best,C[i]};
                }
            }

            cout << m1.x << '\n';
        }

    }
};
