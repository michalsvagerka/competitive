#include "../../../l/lib.h"
// #include "../l/mod.h"

class TaskC {
public:
    vector<vector<int>> E;
    vector<bool> V,P;
    int N;

    void dfs(int u, bool p) {
        if (V[u]) return;
        V[u] = true;
        P[u] = p;
        for (int v:E[u]) dfs(v, !p);
    }

void solve(istream& cin, ostream& cout) {
    cin >> N;
    E.resize(2*N);
    V = vector<bool>(2*N, false);
    vector<pii> Z(N);
    P.resize(2*N);
    for (int i = 0; i < N; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        E[u].push_back(v);
        E[v].push_back(u);

        Z[i] = {u,v};
        E[2*i].push_back(2*i+1);
        E[2*i+1].push_back(2*i);
    }

    for (int i = 0; i < 2*N; ++i) {
        if (!V[i]) dfs(i, true);
    }

    for (int i = 0; i < N; ++i) {
        cout << P[Z[i].x]+1 << ' ' << P[Z[i].y]+1 << '\n';
    }
}
};
