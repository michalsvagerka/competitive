#include "../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        int C; cin >> C;
        vector<string> F(2*C);
        vector<int> P(2*C);
        for (int i = 0; i < C; ++i) {
            cin >> F[2*i] >> P[2*i];
            P[2*i+1] = P[2*i];
            F[2*i+1] = F[2*i];
            reverse(F[2*i+1].begin(),F[2*i+1].end());
        }

        vector2<int> D(N+1,N+1,-1000000000); // begin => length => max profit
        for (int i = 0; i <= N; ++i) {
            D[i][0] = 0;
        }

        vector<bool> A(52), B(52);
        for (int b = N-1; b >= 0; --b) {
            for (int c = 0; c < 2*C; c++) {
                int M = F[c].size();
                if (b+M > N) continue;
                vector2<int> Q(N+1, M+1, -1000000000);
                Q[0][0] = 0;
                for (int l = 1; b+l <= N; ++l) {
                    for (int m = 0; m < M; ++m) {
                        if (S[b+l-1] == F[c][m]) {
                            Q[l][m+1] = max(Q[l][m+1],Q[l-1][m]);
                        }
                    }

                    for (int m = 0; m <= M; ++m) {
                        for (int z = 1; b+l+z <= N; ++z) {
                            Q[l+z][m] = max(Q[l+z][m],Q[l][m] + D[b+l][z]);
                        }
                    }

                    D[b][l] = max(D[b][l], Q[l][M] + P[c]);
                }
            }
        }

        vector<int> Z(N+1,0);
        for (int i = 0; i < N; ++i) {
            for (int l = 1; i+l <= N; ++l) {
                Z[i+l] = max(Z[i+l], Z[i]+D[i][l]);
            }
            Z[i+1] = max(Z[i+1],Z[i]);
        }

        cout << Z[N] << endl;
    }
};
