#include "../l/lib.h"

class DShikAndGame {
public:
    void solve(istream& cin, ostream& cout) {
        int N, E, T; cin >> N >> E >> T;
        vector<ll> X(N+1, 0);
        for (int i = 0; i < N; ++i) cin >> X[i+1];
        vector<ll> D(N+1, 1e18);
        D[0] = E;
        int j = 0;
        ll lo = 1e18;
        for (int i = 1; i <= N; ++i) {
            while (2*(X[i]-X[j+1]) >= T) { lo = min(lo, D[j] - 2 * X[j+1]); ++j; }
            D[i] = lo + 3 * X[i];
            if (j != i) D[i] = min(D[i], D[j] + X[i] + T); 
            D[i] -= X[i];
        }

        cout << D[N] << '\n';
    }
};
