#include "../l/lib.h"
#include "../l/mod.h"

class CRockIsPush {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        if (N == 1 && M == 1) {
            cout << 1 << endl;
            return;
        }
        
        vector<string> A(N); cin >> A;
        vector2<int> D(N, M, 0), R(N, M, 0);
        for (int i = 0; i < N; ++i) {
            for (int j = M-1; j > 0; --j) {
                R[i][j-1] = R[i][j] + (A[i][j] == 'R');
            }
        }

        for (int j = 0; j < M; ++j) {
            for (int i = N-1; i > 0; --i) {
                D[i-1][j] = D[i][j] + (A[i][j] == 'R');
            }
        }

        vector2<FieldMod> L(N, M, 0), U(N, M, 0);
        L[0][0] = U[0][0] = 1;
        if (N > 1) U[1][0] = -U[0][0];
        if (M > 1) L[0][1] = -L[0][0];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (i != 0) U[i][j] += U[i-1][j];
                if (j != 0) L[i][j] += L[i][j-1];
                
                if (i != N-1) U[i+1][j] += L[i][j];
                if (D[i][j] != 0) U[N-D[i][j]][j] -= L[i][j];
                
                if (j != M-1) L[i][j+1] += U[i][j];
                if (R[i][j] != 0) L[i][M-R[i][j]] -= U[i][j];
//                for (int k = i+1; k+D[i][j] < N; ++k) {
//                    U[k][j] += L[i][j];
//                }
//                for (int k = j+1; k+R[i][j] < M; ++k) {
//                    L[i][k] += U[i][j];
//                }
            }
        }
        
        
        cout << L[N-1][M-1] + U[N-1][M-1] << '\n';

    }
};
