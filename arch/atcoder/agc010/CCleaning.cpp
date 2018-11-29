#include "../l/lib.h"
// #include "../l/mod.h"

class CCleaning {
public:
    int N;
    vector<vector<int>> E;
    vector<ll> A;
    
    bool ok;
    ll dfs(int u, int p) {
        ll mx = 0, sm = 0;
        for (int v : E[u]) if (v != p) {
            ll t = dfs(v, u);
            sm += t;
            mx = max(mx, t);
        }

        if (E[u].size() > 1) {
            if (sm > 2 * A[u]) { ok = false; return 0; }
            if (sm < A[u]) { ok = false; return 0; }
            ll up = 2*A[u] - sm;
            ll mix = sm - A[u];
            if (mx > mix + up) { ok = false; return 0; }
            return up;
        } else if (u == 0) {
            if (sm != A[u]) { ok = false; return 0; }
        } else {
            return A[u];
        }
        return 0;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        ok = true;
        E.resize(N);
        A.resize(N);
        cin >> A;
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        ll ans = dfs(0, -1);
        if (ans) ok = false;
        
        cout << (ok ? "YES" : "NO") << '\n';
    }
};
