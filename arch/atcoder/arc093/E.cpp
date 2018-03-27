#include "../../../l/lib.h"
#include "../../../l/mod.h"
#include "../../../l/util.h"

class E {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        if (N < 3) {
            cout << 0 << endl;
            return;
        }
        ll X; cin >> X;
        vector<pair<int,pii>> E(M);
        for (int i = 0; i < M; ++i) {
            int u, v, w; cin >> u >> v >> w;
            --u; --v;
            E[i] = {w, {u,v}};
        }
        sort(E.begin(),E.end());
        int higher = 0;
        int exact = 0;
        int lower = 0;
        for (int i = 0; i < M; ++i) {
            UnionFind U(N);
            ll cost = E[i].x;
            U.unite(E[i].y.x, E[i].y.y);
            for (int j = 0; j < M; ++j) {
                if (U.unite(E[j].y.x, E[j].y.y)) {
                    cost += E[j].x;
                }
            }

            higher += cost > X;
            exact += cost == X;
            lower += cost < X;
        }

        if (exact == 0) {
            cout << 0 << endl;
        } else {
            cout << (FieldMod{2}.pow(exact) - 1 - (lower==0)) * FieldMod{2}.pow(higher+(lower!=0)) << endl;
        }
    }
};
