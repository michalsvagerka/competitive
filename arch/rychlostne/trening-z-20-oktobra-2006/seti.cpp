#include "../l/lib.h"
#include "../l/runtimemod.h"
#include "../l/matrix.h"

class seti {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            ui p; cin >> p;
            string S; cin >> S;
            int N = S.size();
            Matrix<RField> M(N,N,RField(p, 0));
            for (int k = 0; k < N; ++k) {
                M[k][0] = RField(1, p);
                for (int j = 1; j < N; ++j) {
                    M[k][j] = M[k][j-1] * (k+1);
                }
            }
//            cout << M;
            vector<RField> V(N);
            for (int i = 0; i < N; ++i) {
                if (S[i] != '*') {
                    V[i] = 1 + S[i] - 'a';
                } else {
                    V[i] = 0;
                }
            }
            cout << M.solveFor(V);
        }
    }
};
