#include "../l/lib.h"
// #include "../l/mod.h"

class sprievodca {
public:
    void solve(istream& cin, ostream& cout) {
        ui N,K; cin >> N >> K;
        vector2<ui> A(N,N,0);
        for (ui i = 0; i < N; ++i) {
            for (ui j = i+1; j < N; ++j) {
                cin >> A[i][j];
            }
        }
        auto B = A;
        for (ui i = 0; i < N; ++i) {
            for (ui j = N-2; j > i; --j) {
                B[i][j] += B[i][j+1];
            }
        }

        for (ui i = 0; i < N-1; ++i) {
            for (ui j = i+2; j < N; ++j) {
                B[i+1][j] += B[i][j];
            }
        }

        vector2<ui> Z(K, N+1, 0);
        for (int i = 0; i < N-1; ++i) Z[0][i] = B[i][i+1];
        for (int k = 1; k < K; ++k) {
            for (int i = 0; i < N - 1; ++i) {
                for (int j = i+1; j < N-1; ++j) {
                    Z[k][j] = max(Z[k][j], Z[k-1][i] + B[j][j+1] - B[i][j+1]);
                }
            }
        }
        cout << *max_element(Z[K-1].begin(),Z[K-1].end()) << endl;
    }
};
