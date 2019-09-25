#include "../l/lib.h"

class LightShow {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int H, N; cin >> H >> N;
            vector<pii> L(N); cin >> L;
            sort(L.begin(),L.end());
            vector2<int> X(N+1, 2*N+1, 0);
            X[0][N] = 1;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j <= 2*N; ++j) {
                    if (X[i][j] == 0) continue;
                    int bal = j - N;
                    if (L[i].y == 1) {
                        if (bal <= 0) {
                            X[i+1][j-1] = max(X[i+1][j-1], X[i][j] + abs(bal));
                        } else {
                            X[i+1][j] = max(X[i+1][j], X[i][j]);
                            X[i+1][N-1] = max(X[i+1][N-1], X[i][j]);
                        }
                    } else {
                        if (bal >= 0) {
                            X[i+1][j+1] = max(X[i+1][j+1], X[i][j] + abs(bal));
                        } else {
                            X[i+1][j] = max(X[i+1][j], X[i][j]);
                            X[i+1][N+1] = max(X[i+1][N+1], X[i][j]);
                        }
                    }
                }
            }
            int ans = 0;
            for (int i = 0; i <= 2*N; ++i) ans = max(ans, X[N][i]);
            cout << "Case #" << t+1 << ": " << ans-1 << '\n';
        }
    }
};
