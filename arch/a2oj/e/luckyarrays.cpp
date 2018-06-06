#include "../../../l/lib.h"
 #include "../../../l/mod.h"
#include "../../../l/matrix.h"

typedef Field<777777777> F;

class luckyarrays {
public:
    void solve(istream& cin, ostream& cout) {
        int N,M; cin >> N >> M;
        vector2<F> W(3,3); cin >> W;
        Matrix<F> Id(3,3,0); Id[0][0] = Id[1][1] = Id[2][2] = 1;
        if (N == 1) {
            for (int i = 0; i < M; ++i) {
                int j,k; cin >> j >> k;
                cout << (k == 0 ? 3 : 1) << '\n';
            }
            return;
        }


        vector<Matrix<F>> T;
        for (int i = 0; i < 4; ++i) {
            T.emplace_back(W, F(0));
            T[i].transpose();

            if (i != 0) {
                for (int j = 0; j < 3; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        if (j != i - 1) T[i][j][k] = 0;
                    }
                }
            }
        }

        int S = 1<<logceil(N-1);
        vector<Matrix<F>> Z(2*S, Id);
        for (int i = 1; i < N; ++i) Z[S+i-1] = T[0];
        for (int i = S-1; i > 0; --i) Z[i] = Z[2*i+1] * Z[2*i];

        vector<int> A(N, 0);
        for (int i = 0; i < M; ++i) {
            int j,k; cin >> j >> k; --j;
            A[j] = k;
            if (j != 0) {
                int h = S+j-1;
                Z[h] = T[k];
                h /= 2;
                while (h > 0) { Z[h] = Z[2*h+1] * Z[2*h]; h/=2; }
            }

            vector<F> Q(3, 0);
            if (A[0] == 0) Q[0] = Q[1] = Q[2] = 1;
            else Q[A[0]-1] = 1;
            Q = Z[1]*Q;
            cout << Q[0]+Q[1]+Q[2] << '\n';
        }

    }
};
