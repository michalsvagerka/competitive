#include "../l/lib.h"
#include "../l/util.h"
#include "../l/flow.h"

class GZoningRestrictions {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, H; cin >> N >> H >> M;
        PushRelabel<int> P(N*H+M+3);

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < H; ++j) {
                P.AddEdge(0, 1+i*H + j, 2*j+1);
            }
        }

        vector<int> S(M);
        for (int k = 0; k < M; ++k) {
            int L, R, X, C;
            cin >> L >> R >> X >> C;
            for (int i = L-1; i < R; ++i) {
                for (int j = X; j < H; ++j) {
                    P.AddEdge(1 + i * H + j, N * H + 1 + k, 100000);
                    S[k] += 2*j+1;
                }
            }
            P.AddEdge(N*H+1+k, N*H+M+2, C);
        }

        auto a = P.GetMaxFlow(0, N*H+M+2);

        cout << N*H*H - a << endl;
    }
};
