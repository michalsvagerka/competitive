#include "../l/lib.h"
// #include "../l/mod.h"

class kripke {
public:
    int N, M, K;
    vector<bool> V;
    vector<vector<int>> E, F;
    vector2<bool> P;
    int P1, P2;

    void dfs1(int u) {
        if (V[u] || P[u][P2]) return;

        V[u] = true;
        for (int v:F[u]) {
            P[v][P2] = false;
            dfs1(v);
        }
    }

    void dfs2(int u) {
        if (V[u]) return;
        V[u] = true;
        for (int v:F[u]) {
            if (P[v][P1]) dfs2(v);
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> M >> K;
        P = vector2<bool>(N, K, false);
        for (int i = 0; i < N; ++i) {
            int c; cin >> c;
            for (int j = 0; j < c; ++j) {
                char p; cin >> p;
                P[i][p-'a'] = true;
            }
        }

        E.resize(N); F.resize(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            F[v].push_back(u);
        }

        string S; cin >> S;
        P1 = S[2]-'a';
        P2 = S[7]-'a';

        V = vector<bool>(N, false);
        for (int i = 0; i < N; ++i) dfs1(i);

        V = vector<bool>(N, false);
        for (int i = 0; i < N; ++i) if (P[i][P2]) dfs2(i);

        cout << count(V.begin(),V.end(),true) << '\n';
        for (int i = 0; i < N; ++i) {
            if (V[i]) cout << i+1 << '\n';
        }
    }
};
