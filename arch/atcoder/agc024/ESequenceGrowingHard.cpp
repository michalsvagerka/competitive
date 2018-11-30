#include "../l/lib.h"
 #include "../l/runtimemod.h"

class ESequenceGrowingHard {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K, M;
        cin >> N >> K >> M;

        vector<RField> R(N+1, RField(0, M));
        R[0] = {1, M};
        for (int i = 0; i < K; ++i) {
            vector2<RField> Z(N+1, N+1, RField(0, M));
            for (int j = 0; j <= N; ++j) Z[0][j] = R[j];
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k <= N; ++k) {
                    if (k >= j && k != N) Z[j+1][k+1] += Z[j][k] * (k-j+1);

                    Z[j+1][k] += Z[j][k];
                }
            }
            for (int j = 0; j <= N; ++j) R[j] = Z[N][j];
        }
        cout << R[N] << endl;
    }
};
