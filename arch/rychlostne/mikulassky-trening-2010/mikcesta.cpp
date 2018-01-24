#include "../l/lib.h"
#include "../l/mod.h"

class mikcesta {
public:
    void solve(istream& cin, ostream& cout) {
        ui N; cin >> N;
        vector<ui> D(N, 0);
        for (int i = 0; i < 2*N-2; ++i) {
            int u; cin >> u; --u; D[u]++;
        }

        auto F = Field<1000000009>::fact(N+1);
        auto ans = F[D[0]];
        for (int j = 1; j < N; ++j) {
            ans *= F[D[j]-1];
        }
        cout << ans << endl;
    }
};
