#include "../l/lib.h"

class DChloeAndPleasantPrizes {
public:
    int N;
    vector<int> A;
    vector<vector<int>> E;
    ll ans = -1e18;

    pair<ll,ll> dfs(int u, int p) {
        ll tot = A[u], best = -1e18;
        for (int v : E[u]) {
            if (v != p) {
                auto x = dfs(v, u);
                ans = max(ans, best + x.y);
                best = max(best, x.y);
                tot += x.x;
            }
        }

        best = max(best, tot);
        return {tot, best};
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        A.resize(N); cin >> A;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        dfs(0, -1);
        if (ans < -9e17) {
            cout << "Impossible\n";
        } else {
            cout << ans << '\n';
        }
    }
};
