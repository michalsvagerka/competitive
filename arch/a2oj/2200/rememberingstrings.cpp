#include "../../../l/lib.h"
// #include "../l/mod.h"

class rememberingstrings {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<string> I(N); cin >> I;
        vector2<int> A(N,M); cin >> A;

        vector<int> L(N, 1e9);
        vector2<int> S(M, 26, 0), H(M, 26, 0), T(M, 26, 0);
        int base = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                L[j] = min(L[j], A[j][i]);

                int k = I[j][i] - 'a';
                H[i][k] = max(H[i][k], A[j][i]);
                S[i][k] += A[j][i];
                T[i][k] |= (1<<j);
            }

            for (int k = 0; k < 26; ++k) {
                if (__builtin_popcount(T[i][k]) == 1) {
                    base |= T[i][k];
                }
            }
        }

        vector<int> D(1<<N, 0);
        for (int i = 0; i < (1<<N); ++i) {
            for (int j = 0; j < N; ++j) {
                if (i&(1<<j) && !((1<<j)&base)) {
                    D[i] += L[j];
                }
            }
        }

        for (int i = 0; i < M; ++i) {
            for (int k = 0; k < 26; ++k) {
                if (__builtin_popcount(T[i][k]) < 2) continue;
                for (int j = (1<<N)-1; j >= 0; --j) {
                    D[j|T[i][k]] = min(D[j|T[i][k]], D[j] + S[i][k] - H[i][k]);
                }
            }
        }
        cout << D.back() << endl;
    }
};
