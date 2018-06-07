#include "../l/lib.h"
// #include "../l/mod.h"

class doubleprofiles {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N, M;
        vector<vector<int>> E(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            if (u > v) swap(u,v);
            E[u].push_back({u,v});
            E[v].push_back({u,v});
        }
    }
};
