#include "../l/lib.h"
#include "../l/random.h"
#include "../l/geo.h"

class miniplanar {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<pii> E(M);
        for (int i = 0; i < M; ++i) cin >> E[i].x >> E[i].y;
        random_int R(0, 100);
        for (int t = 0; t < 100000; ++t) {
            vector<pll> P(N);
            for (int i = 0; i < N; ++i) P[i] = {R(rng),R(rng)};
            bool ok = true;
            for (int i = 0; i < N; ++i) {
                for (int j = i+1; j < N; ++j) {
                    ok &= P[i] != P[j];
                }
            }
            for (int i = 0; i < M; ++i) {
                for (int j = i+1; j < M; ++j) {
                    ok &= E[j].x == E[i].x || E[j].y == E[i].x || E[j].x == E[i].y || E[j].y == E[i].y || !segmentsIntersect(P[E[i].x],P[E[i].y],P[E[j].x],P[E[j].y]);
                }
            }

            if (ok) {
                cout << "YES\n";
                return;
            }
        }
        cout << "NO\n";

    }
};
