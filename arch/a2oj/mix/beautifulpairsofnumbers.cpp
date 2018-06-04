#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class beautifulpairsofnumbers {
public:
    void solve(istream& cin, ostream& cout) {
        vector2<FieldMod> D(50, 1001, 0);
        D[0][0] = 1;
        for (int d = 0; d < 1001; ++d) {
            for (int i = 48; i >= 0; --i) {
                for (int c = 0; c+d <= 1000; ++c) {
                    D[i+1][c+d] += D[i][c];
                }
            }
        }

        auto F = FieldMod::fact(1100);
        auto I = FieldMod::invfact(1100);

        vector2<FieldMod> E(50, 1001, 0);
        for (int k = 1; k < 50; ++k) {
            for (int n = 1; n <= 1000; ++n) {
                for (int d = 0; d <= n-k; ++d) {
                    int a = n-d;
                    E[k][n] += D[k][d] * F[a] * I[a-k];
                }
            }
        }

        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, K; cin >> N >> K;
            if (K >= 50) {
                cout << "0\n";
            } else {
                cout << E[K][N] << '\n';
            }
        }

    }
};
