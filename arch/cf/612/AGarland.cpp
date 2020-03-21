#include "../l/lib.h"

class AGarland {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> A(N); cin >> A;
        vector<bool> U(N+1, false);
        for (int a: A) if (a > 0) U[a] = true;
        int odd = 0, even = 0;
        for (int i = 1; i <= N; ++i) {
            if (!U[i]) {
                if (i%2 == 1) ++odd; else ++even;
            }
        }

        vector3<int> D(N+1, N+1, 2, 10000);
        D[0][0][0] = 0;
        D[0][0][1] = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j <= N; ++j) {
                for (int k = 0; k < 2; ++k) {
                    if (D[i][j][k] == 10000) continue;
                    if (A[i] != 0) {
                        D[i+1][j][A[i]%2] = min(D[i+1][j][A[i]%2], D[i][j][k] + (A[i]%2!=k));
                    } else {
                        for (int l = 0; l < 2; ++l) {
                            D[i+1][j+l][l] = min(D[i+1][j+l][l], D[i][j][k] + (l!=k));
                        }
                    }
                }
            }
        }
        
        cout << min(D[N][odd][0], D[N][odd][1]) << '\n';
    }
};
