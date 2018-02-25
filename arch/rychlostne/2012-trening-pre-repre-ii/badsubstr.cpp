#include "../../../l/lib.h"
// #include "../l/mod.h"
#include "../../../l/string.h"

class badsubstr {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string A, B; cin >> A >> B;
        KMP<string> AR(A), BR(B);
        int K = A.size(), L = B.size();
        vector3<ull> D(N+1, K, L, 0);
        D[0][0][0] = 1;
        string ch = "ABC";
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < K; ++k) {
                for (int l = 0; l < L; ++l) {
                    for (char c: ch) {
                        int nK = AR.advance(k, c);
                        int nL = BR.advance(l, c);
                        if (nK != K && nL != L)
                            D[i+1][nK][nL] += D[i][k][l];
                    }
                }
            }
        }

        ull ans = 0;
        for (int k = 0; k < K; ++k) {
            for (int l = 0; l < L; ++l) {
                ans += D[N][k][l];
            }
        }
        cout << ans << endl;
    }
};
