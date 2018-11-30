#include "../l/lib.h"
// #include "../l/mod.h"

class CSquaredGraph {
public:
    vector<vector<int>> E;
    vector<bool> V, P;

    bool bipartite(int u, bool p) {
        if (V[u]) return P[u] == p;
        V[u] = true;
        P[u] = p;

        bool ans = true;
        for (int v : E[u]) {
            ans &= bipartite(v, !p);
        }
        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        E.resize(N);
        V.assign(N, false); P.resize(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        ll bip = 0, reg = 0, empty = 0;
        for (int i = 0; i < N; ++i) {
            if (!V[i]) {
                if (E[i].empty()) ++empty;
                else if (bipartite(i, true)) bip++;
                else reg++;
            }
        }

        ll ans = 2 * N * empty - empty * empty + 2 * bip * bip + reg * reg + 2 * bip * reg; 
        cout << ans << '\n';
    }
};
