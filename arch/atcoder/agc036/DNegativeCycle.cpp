#include "../l/lib.h"

class DNegativeCycle {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector2<int> A(N, N, 0);
        vector2<ll> B(N, N+1, 0);
        vector2<ll> C(N+1, N, 0);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i != j) cin >> A[i][j];
                B[i][j+1] = B[i][j] + A[i][j];
                C[i+1][j] = C[i][j] + A[i][j];
            }
        }

        constexpr ll MX = 1e18;
        vector2<ll> D(N, N+1, MX);
        D[0][0] = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i; j < N; ++j) {
                if (D[i][j] != MX) {
                    ll val = D[i][j];
                    for (int k = j+1; k < N; ++k) val += B[k][j] - B[k][i];
                    for (int k = j+1; k <= N; ++k) {
                        D[j][k] = min(D[j][k], val);
                        if (k != N) val += C[k][k] - C[j][k] - B[k][j] + B[k][i];
                    }
                }
            }
        }


        ll ans = MX;
        for (int i = 0; i < N; ++i) ans = min(ans, D[i][N]);
        cout << ans << endl;
    }
};
