#include "../l/lib.h"
#include "../l/mod.h"

class FLeftmostBall {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        if (K == 1) {
            cout << 1 << endl;
            return;
        }
        
        auto F = FieldMod::fact(N*K);
        auto I = FieldMod::invfact(N*K);
        
        vector2<FieldMod> A(N+1, N+1, 0);
        A[0][0] = 1;
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (i != N) {
                    A[i+1][j] += A[i][j];
                }
                
                if (i != j) {
                    int k = (N - (j+1)) * (K-1) + (N - i);
                    A[i][j+1] += A[i][j] * F[k + K - 2] * I[k];
                }
            }
        }
        cout << A[N][N] * F[N] * I[K-2].pow(N) << endl;
    }
};
