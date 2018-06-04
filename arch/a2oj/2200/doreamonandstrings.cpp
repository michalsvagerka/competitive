#include "../../../l/lib.h"
// #include "../l/mod.h"

class doreamonandstrings {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        string P; cin >> P;
        int N = S.size(), M = P.size();

        vector<int> R(N, N+1);
        for (int i = 0; i < N; ++i) {
            int j = i, k = 0;
            while (j < N && k < M) {
                if (P[k] != S[j]) ++j;
                else { ++k; ++j; }
            }
            if (k == M) R[i] = j;
        }

        vector2<int> W(N+2, N/M+1, 1e6);
        W[0][0] = 0;
        for (int i = 0; i < N; ++i) {
            for (int r = 0; r <= N/M; ++r) {
                if (W[i][r] < 1e6) {
                    W[R[i]][r + 1] = min(W[R[i]][r + 1], W[i][r] + R[i] - i - M);
                    W[i + 1][r] = min(W[i + 1][r], W[i][r]);
                }
            }
        }

        vector<int> A(N+1, 0);
        for (int j = 1; j <= N/M; ++j) if (W[N][j] < 1e6) A[W[N][j]] = j;
        for (int j = 1; j <= N; ++j) A[j] = min((N-j)/M, max(A[j], A[j-1]));
        cout << A;
    }
};
