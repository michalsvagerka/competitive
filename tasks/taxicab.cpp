#include "../l/lib.h"
#include "../l/graph.h"
// #include "../l/mod.h"

class taxicab {
public:
    int dist(const pii&a, const pii&b) {
        return abs(a.x-b.x)+abs(a.y-b.y);
    }

    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        for (ui t = 0; t < T; ++t) {
            ui N; cin >> N;
            vector<pair<int,pair<pii,pii>>> R(N);
            for (ui i = 0; i < N; ++i) {
                ui h,m; char c; cin >> h >> c >> m;
                R[i].x = h*60 + m;
                cin >> R[i].y.x.x >> R[i].y.x.y >> R[i].y.y.x >> R[i].y.y.y;
            }

            Bipartite G(N, N);
            for (ui i = 0; i < N; ++i) {
                for (ui j = i+1; j < N; ++j) {
                    if (R[i].x + dist(R[i].y.x,R[i].y.y) + dist(R[i].y.y,R[j].y.x) < R[j].x) {
                        G.addEdge(i,j+N);
                    }
                }
            }
            cout << N-G.matchingSize() << endl;
        }
    }
};
