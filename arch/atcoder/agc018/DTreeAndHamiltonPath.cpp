#include "../l/lib.h"
// #include "../l/mod.h"

class DTreeAndHamiltonPath {
public:
    vector<vector<pii>> E;
    vector<int> S, C;
    ll ans;
    int N;

    int size(int u, int p) {
        int s = 1;
        for (pii v : E[u]) if (v.x != p) s += size(v.x, u);
        return S[u] = s;
    }

    void dfs(int u, int p) {
        int s = N - S[u];
        for (pii v:E[u]) if (v.x!=p) s = max(s, S[v.x]);
        if (2*s <= N) C.push_back(u);
        for (pii v:E[u]) {
            if (v.x!=p) {
                ans += 2 * ll(v.y) * min(N-S[v.x], S[v.x]);
                dfs(v.x,u);
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        ans = 0;
        E.resize(N);
        S.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            --u;
            --v;
            E[u].push_back({v,c});
            E[v].push_back({u,c});
        }
        size(0, -1);
        dfs(0, -1);
        if (C.size() == 1) {
            int lo = 1e9;
            for (pii v : E[C[0]]) lo = min(lo, v.y);
            ans -= lo;
        } else {
            for (pii v : E[C[0]]) if (v.x == C[1]) ans -= v.y;
        }
        cout << ans << '\n';

    }
};
