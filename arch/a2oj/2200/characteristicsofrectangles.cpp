#include "../../../l/lib.h"
// #include "../l/mod.h"

class characteristicsofrectangles {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector2<int> A(N, M);
        cin >> A;

        vector2<int> S(M,M,0);
        int ans = 0;
        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < M; ++i) {
                for (int j = i+1; j < M; ++j) {
                    ans = max(ans, min(S[i][j], min(A[k][i], A[k][j])));
                    S[i][j] = max(S[i][j], min(A[k][i], A[k][j]));
                }
            }
        }
        cout << ans << endl;
    }
};
