#include "../../../l/lib.h"
#include "../../../l/util.h"

class letiska {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        UnionFind U(N);
        vector<pair<pii,pii>> E(M);
        for (int i = 0; i < M; ++i) {
            cin >> E[i];
            U.unite(E[i].x.x-1, E[i].x.y-1);
        }

        if (U.comp > 1) {
            cout << "-1\n";
            return;
        }

        double ans = bshd(0, 1e8, [&](double d) {
            sort(E.begin(),E.end(),[&](const pair<pii,pii>&a, const pair<pii,pii>&b) {
                return a.y.x - d * a.y.y > b.y.x - d * b.y.y;
            });

            double tot = 0;
            UnionFind V(N);
            for (auto&e:E) {
                if (V.unite(e.x.x-1, e.x.y-1) || e.y.x - d * e.y.y >= 0) {
                    tot += e.y.x - d * e.y.y;
                }
            }
            return tot >= 0;
        });

        cout << fixed << setprecision(15) << ans << endl;
    }
};
