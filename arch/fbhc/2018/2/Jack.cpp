#include "../l/lib.h"
// #include "../l/mod.h"

class Jack {
public:
    vector<vector<int>> E;
    vector<int> C;

ll dfs(int u, set<int> &V) {
    ll ans = 0;
    V.insert(u);
    for (int v : E[u]) {
        set<int> G;
        ans += dfs(v, G);
        if (G.size() > V.size()) swap(G,V);
        for (int g:G) V.insert(g);
    }

    for (int c = 0; c < C[u]; ++c) {
        if (V.empty()) break;
        auto it = prev(V.end());
        ans += *it;
        V.erase(it);
    }
    return ans;
}

void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        ll N, M, A, B;
        cin >> N >> M >> A >> B;
        cout << "Case #" << t+1 << ": ";
        E.clear(); E.resize(N);
        C = vector<int>(N, 0);
        for (int i = 1; i < N; ++i) {
            int p; cin >> p;
            E[p].push_back(i);
        }

        for (int i = 0; i < M; ++i) {
            int c = (A * i + B) % N;
            C[c]++;
        }

        set<int> X;
        cout << dfs(0, X) << '\n';
    }
}
};
