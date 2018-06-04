#include "../../../l/lib.h"
// #include "../l/mod.h"

constexpr ll infty = 1e18;

class topsecrettask {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K, S; cin >> N >> K >> S;
        S = min(S, N*(N-1)/2);
        vector<int> Q(N); cin >> Q;
        vector2<ll> DP(K+1, S+1, infty);
        DP[0][0] = 0;
        for (int i = 0; i < N; ++i) {
            vector2<ll> E(K+1, S+1, infty);
            for (int j = 0; j <= K; ++j) {
                for (int k = 0; k <= S; ++k) {
                    if (DP[j][k] == infty) continue;
                    if (k+K-j <= S) E[j][k+K-j] = min(E[j][k+K-j], DP[j][k]);
                    if (j != K) E[j+1][k] = min(E[j+1][k], DP[j][k] + Q[i]);
                }
            }
            swap(E,DP);
        }

        ll ans = infty;
        for (int l = 0; l <= S; ++l) ans = min(ans, DP[K][l]);
        cout << ans << endl;
    }
};
