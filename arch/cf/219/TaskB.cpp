#include "../l/lib.h"
// #include "../l/mod.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int N, M, Q; cin >> N >> M >> Q;
    vector<string> S(N); cin >> S;
    vector2<int> P(N+1, M+1, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            P[i+1][j+1] = P[i][j+1] + P[i+1][j] - P[i][j] + (S[i][j] - '0');
        }
    }

    vector4<int> C(N, M, N, M, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for (int k = i; k < N; ++k) {
                for (int l = j; l < M; ++l) {
                    C[i][j][k][l] += (P[k+1][l+1] - P[k+1][j] - P[i][l+1] + P[i][j] == 0);
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int k = i; k < N; ++k) {
            for (int l = 0; l < M; ++l) {
                for (int j = l-1; j >= 0; --j) {
                    C[i][j][k][l] += C[i][j+1][k][l];
                }
            }
        }
    }


    for (int j = 0; j < M; ++j) {
        for (int k = 0; k < N; ++k) {
            for (int l = 0; l < M; ++l) {
                for (int i = k-1; i >= 0; --i) {
                    C[i][j][k][l] += C[i+1][j][k][l];
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for (int k = i; k < N-1; ++k) {
                for (int l = j; l < M; ++l) {
                    C[i][j][k+1][l] += C[i][j][k][l];
                }
            }
        }
    }


    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            for (int k = i; k < N; ++k) {
                for (int l = j; l < M-1; ++l) {
                    C[i][j][k][l+1] += C[i][j][k][l];
                }
            }
        }
    }

    for (int q = 0; q < Q; ++q) {
        int a,b,c,d; cin >> a >> b >> c >> d;
        cout << C[a-1][b-1][c-1][d-1] << '\n';
    }
//    cout << C[0][0];

}
};
