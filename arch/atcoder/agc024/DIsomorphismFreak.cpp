#include "../l/lib.h"
// #include "../l/mod.h"

class DIsomorphismFreak {
public:
    vector<vector<int>> E;
    vector<int> D;

    void dfs(int u, int p, int d) {
        D[d] = max(D[d], (int)E[u].size() - (p!=-1));
        for (int v : E[u]) if (v != p) dfs(v, u, d+1);
    }
    

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        pair<int, ll> best = {N, 0};
        for (int i = 0; i < N; ++i) {
            D.assign(N, 0);
            dfs(i, -1, 0);
            ll x = 1;
            int j = 0;
            while (j < N && D[j]) x *= D[j++];
            best = min(best, {j+1, x});
        }

        for (int u = 0; u < N; ++u) {
            for (int v : E[u]) {
                D.assign(N, 0);
                dfs(u, v, 0);
                dfs(v, u, 0);
                ll x = 2;
                int j = 0;
                while (j < N && D[j]) x *= D[j++];
                best = min(best, {j+1, x});
            }
        }

        cout << best << '\n';
    }
};
