#include "../l/lib.h"

class ALinovaAndKingdom {
public:
    int N, K;
    vector<vector<int>> E;
    vector<int> S, D;

    int dfs(int u, int p, int d) {
        S[u] = 1;
        D[u] = d;
        for (int v: E[u]) {
            if (v != p) {
                S[u] += dfs(v, u, d+1);
            }
        }
        return S[u];
    }
    void solve(istream& cin, ostream& cout) {
        cin >> N >> K; K = N-K;
        E.resize(N);
        for (int i = 0; i < N-1; ++i) {
            int u,v; cin >> u >> v; --u; --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        S.resize(N);
        D.resize(N);
        dfs(0, -1, 1);
        for (int i = 0; i < N; ++i) S[i] -= D[i];
        sort(S.begin(),S.end());
        reverse(S.begin(),S.end());
        ll tot = 0;
        for (int i = 0; i < K; ++i) tot += S[i];
        cout << tot << '\n';
    }
};
