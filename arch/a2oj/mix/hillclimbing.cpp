#include "../../../l/lib.h"
#include "../../../l/geo.h"
#include "../../../l/graph.h"

class hillclimbing {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        Tree T(N);
        vector<Point<ll>> P(N); cin >> P;
        vector<pair<Point<ll>,int>> S{{P[N-1],N-1}};
        for (int p = N-2; p >= 0; --p) {
            while (S.size() >= 2 && ccw(S[S.size()-2].x, S[S.size()-1].x, P[p]) < 0) {
                S.pop_back();
            }
            T.addEdge(p, S[S.size()-1].y);
            S.push_back({P[p],p});
        }
        T.setRoot(N-1);

        int M; cin >> M;
        vector<int> Ans(M);
        for (int i = 0; i < M; ++i) {
            int a,b; cin >> a >> b; --a; --b;
            Ans[i] = T.lca(a,b)+1;
        }
        cout << Ans;
    }
};
