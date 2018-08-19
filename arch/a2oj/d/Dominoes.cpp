#include "../l/lib.h"
 #include "../l/mod.h"

class Dominoes {
public:
void solve(istream& cin, ostream& cout) {
    int N, M; cin >> N >> M;
    vector<string> S(4*N+1); cin >> S;
    vector2<bool> H(N,M,false), V(N,M,false);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int cnt = 0;
            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 3; ++l) {
                    cnt += S[4*i+1+k][4*j+1+l] == 'O';
                }
            }
            if (cnt == 6) {
                H[i][j] = S[4*i+1][4*j+2] == 'O';
                V[i][j] = !H[i][j];
            } else if (cnt == 2 || cnt == 3) {
                H[i][j] = S[4*i+1][4*j+1] == 'O';
                V[i][j] = !H[i][j];
            } else {
                H[i][j] = V[i][j] = true;
            }
        }
    }

    vector<bool> Col(M, N%2==0);
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            Col[i] = Col[i] && V[j][i];
        }
    }

    vector<FieldMod> C(M+1, 0);
    C[0] = 1;
    for (int m = 0; m < M; ++m) {
        if (Col[m]) C[m+1] += C[m];

        if (m != M-1) {
            vector<FieldMod> Z(N + 1, 0);
            Z[0] = 1;
            for (int i = 0; i < N; ++i) {
                if (H[i][m] && H[i][m+1]) Z[i+1] += Z[i];
                if (i != N-1 && V[i][m] && V[i+1][m] && V[i][m+1] && V[i+1][m+1]) Z[i+2] += Z[i];
            }
            C[m+2] += C[m] * (Z[N] - (Col[m]&&Col[m+1]));
        }
    }
    cout << C[M] << endl;
}
};
