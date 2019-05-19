#include "../l/lib.h"
#include "../l/mincostmaxflow.h"

class EPetyaAndPipes {
public:
    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector2<int> L(N,N); cin >> L;
        cout << bsh(0, (int)5e7, [&](int f) {
            MinCostMaxFlow<int,int> F(N+1, 0, N);
            F.addEdge(N - 1, N, f, 0);
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (L[i][j]) {
                        F.addEdge(i, j, L[i][j], 0);
                        F.addEdge(i, j, K, 1);
                    }
                }
            }
            pii r = F.minCostMaxFlow();
            return r.x == f && r.y <= K;
        }) << '\n';
    }
};
