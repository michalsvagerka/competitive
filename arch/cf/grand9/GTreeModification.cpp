#include "../l/lib.h"

class GTreeModification {
public:
    int N;
    vector<vector<int>> E;
    vector<bool> P;

    void dfs(int u, int p, bool par) {
        P[u] = par;
        for (int v: E[u]) {
            if (v!=p) {
                dfs(v, u, !par);
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N-1; ++i) {
            int u,v; cin >> u >> v;
            --u; --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        P.resize(N);
        dfs(0, -1, false);
        int c = count(P.begin(),P.end(),false);
        cout << min(c, N-c)-1 << '\n';

    }
};
