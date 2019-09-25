#include "../l/lib.h"

int X[4003][4003];

class guias {
public:
    void solve(istream& cin, ostream& cout) {
        string A, B; cin >> A >> B;
        int N = A.size(), M = B.size();
        for (int i = 0; i <= N+1; ++i) {
            for (int j = 0; j <= M+1; ++j) {
                X[i][j] = 10000;
            }
        }

        vector2<int> G(2, N+2, -1), H(2, M+2, -1);
        G[0][N] = G[1][N] = G[0][N+1] = G[1][N+1] = N;
        H[0][M] = H[1][M] = H[0][M+1] = H[1][M+1] = M;
        for (int i = N-1; i >= 0; --i) {
            G[0][i] = G[0][i+1];
            G[1][i]= G[1][i+1];
            G[A[i]-'0'][i] = i;
        }

        for (int i = M-1; i >= 0; --i) {
            H[0][i] = H[0][i+1];
            H[1][i] = H[1][i+1];
            H[B[i]-'0'][i] = i;
        }
        
        X[0][0] = 0;
        for (int i = 0; i <= N+1; ++i) {
            for (int j = 0; j <= M+1; ++j) {
                for (int k = 0; k < 2; ++k) {
                    int a = G[k][i] + 1;
                    int b = H[k][j] + 1;
                    if (X[a][b] > X[i][j] + 1) {
                        X[a][b] = X[i][j] + 1;
                    }
                }
            }
        }
        
        for (int i = N+1; i >= 0; --i) {
            for (int j = M+1; j >= 0; --j) {
                if (i == N+1 && j == M+1) continue;
                bool ok = false;
                for (int k = 0; k < 2; ++k) {
                    int a = G[k][i] + 1;
                    int b = H[k][j] + 1;
                    ok |= X[a][b] == X[i][j] + 1;
                }
                if (!ok) X[i][j] = -1;
            }
        }

        int i = 0, j = 0;
        while (i != N+1 || j != M+1) {
            for (int k = 0; k < 2; ++k) {
                int a = G[k][i] + 1;
                int b = H[k][j] + 1;
                if (X[a][b] == X[i][j] + 1) {
                    cout << k;
                    i = a;
                    j = b;
                    break;
                }
            }
        }
        cout << endl;
    }
};
