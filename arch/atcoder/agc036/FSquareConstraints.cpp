#include "../l/lib.h"
#include "../l/runtimemod.h"

class FSquareConstraints {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> LO(2*N, 2*N), HI(2*N, 0);
        for (int i = 0; i < 2*N; ++i) {
            for (int j = 0; j < 2*N; ++j) {
                if (i*i + j*j <= 4*N*N && i*i + j*j >= N*N) {
                    LO[i] = min(LO[i], j);
                    HI[i] = max(HI[i], j+1);
                }
            }
        }
        
        vector<pii> X;
        for (int i = 0; i < N; ++i) X.push_back({LO[i], -i});
        for (int i = N; i < 2*N; ++i) X.push_back({HI[i], -i});
        sort(X.begin(),X.end());

        MOD = M;
        RField ans = 0;
        for (int K = 0; K <= N; ++K) {
            vector2<RField> D(2*N+1, K+1, 0);
            D[0][0] = 1;
            int left = 0;
            for (int i = 0; i < 2*N; ++i) {
                int y = -X[i].y;
                for (int j = 0; j <= K; ++j) {
                    if (y >= N) {
                        D[i+1][j] += D[i][j] * max(0, X[i].x - (i + j - left));
                    } else {
                        if (j != K) {
                            D[i+1][j+1] += D[i][j] * max(0, X[i].x - (i + j - left));
                        }

                        D[i+1][j] += D[i][j] * max(0, HI[y] - (N + K + left - j));
                    }
                }
                left += y < N;
            }

            if (K%2 == 0) {
                ans += D[2*N][K];
            } else {
                ans -= D[2*N][K];
            }
        }

        cout << ans << endl;

    }
};
