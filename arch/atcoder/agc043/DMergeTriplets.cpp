#include "../l/lib.h"
#include "../l/runtimemod.h"

class DMergeTriplets {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        MOD = M;

        vector2<RField> D(3*N+1, 3*N+1, 0);
        vector2<RField> Mul(3*N+1, N+1, 0);
        for (int i = 0; i <= 3*N; ++i) Mul[i][0] = 1;

        D[0][0] = 1;
        for (int i = 0; i < 3 * N; ++i) {
            for (int z = 0; z < 3*N-i; ++z) {
                D[i][z+1] += D[i][z] * (z+1);
                D[i+1][z] += D[i][z];
            }
            RField div = RField{1}/D[i+1][0];
            for (int k = 1; k <= N; ++k) {
                Mul[i+1][k] += D[i][0] * Mul[i][k];
                if (i >= 1) Mul[i+1][k] += D[i-1][1] * Mul[i-1][k-1];
                if (i >= 2) Mul[i+1][k] += D[i-2][2] * Mul[i-2][k-1];
                Mul[i+1][k] *= div;
            }
        }

        RField ans = 0;
        for (int k = 0; k <= N; ++k) ans += Mul[3*N][k];
        cout << ans * D[3*N][0] << endl;
    }
};
