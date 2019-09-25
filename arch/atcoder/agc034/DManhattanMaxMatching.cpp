#include "../l/lib.h"
#include "../l/mincostmaxflow.h"

class DManhattanMaxMatching {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        MinCostMaxFlow<ll, ll> G(2*N+6, 2*N, 2*N+5);
        for (int i = 0; i < N; ++i) {
            int x, y, c; cin >> x >> y >> c;
            G.addEdge(2*N, i, c, 0);
            G.addEdge(i, 2*N+1, c, x+y);
            G.addEdge(i, 2*N+2, c, x-y);
            G.addEdge(i, 2*N+3, c, -x+y);
            G.addEdge(i, 2*N+4, c, -x-y);
        }

        for (int i = 0; i < N; ++i) {
            int x, y, c; cin >> x >> y >> c;
            G.addEdge(N+i, 2*N+5, c, 0);
            G.addEdge(2*N+4, N+i, c, x+y);
            G.addEdge(2*N+3, N+i, c, x-y);
            G.addEdge(2*N+2, N+i, c, -x+y);
            G.addEdge(2*N+1, N+i, c, -x-y);
        }

        auto g = G.minCostMaxFlow();
        cout << -g.y << endl;
    }
};
