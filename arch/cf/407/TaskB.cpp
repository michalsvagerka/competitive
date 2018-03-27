#include "../l/lib.h"
#include "../l/util.h"

class TaskB {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        UnionFind U(N);
        vector<int> D(N);
        vector<bool> L(N, false);
        int l = 0;
        for (int i = 0; i < M; ++i) {
            int u,v; cin >> u >> v;
            --u; --v;
            if (u!=v) {
                D[u]++;
                D[v]++;
            } else {
                L[u] = true;
            }
            U.unite(u,v);
        }

        int z = 0;
        for (int i = 0; i < N; ++i) {
            z += !L[i] && (D[i] == 0);
        }

        if (U.comp != 1 + z || M < 2) {
            cout << "0\n";
        } else {
            l = count(L.begin(),L.end(),true);
            ll ans = ll(l) * (l-1);
            for (int i = 0; i < N; ++i) {
                ans += ll(D[i]) * (D[i]-1);
            }
            cout << ans/2 + ll(M-l)*l << endl;
        }
    }
};
