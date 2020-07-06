#include "../l/lib.h"

class BNeighborGrid {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M; cin >> N >> M;
            vector2<int> A(N, M); cin >> A;
            vector2<int> B(N, M, 0);
            bool ok = true;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    B[i][j] += (i!=0);
                    B[i][j] += (i!=N-1);
                    B[i][j] += (j!=0);
                    B[i][j] += (j!=M-1);
                    ok &= B[i][j] >= A[i][j];
                }
            }
            if (ok) {
                cout << "YES\n";
                for (auto&b:B)cout<<b;
            } else {
                cout << "NO\n";
            }

        }
    }
};
