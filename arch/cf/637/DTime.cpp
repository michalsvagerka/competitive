#include "../l/lib.h"

class DTime {
public:
    vector<pii> Sol;
    vector<vector<int>> E;

    void dfs(int u, int p, int val) {
        int beg = val;
        int deg = E[u].size();

        Sol.push_back({u, val});
        int lo = max(0, val-deg);
        int hi = lo + deg;
        for (int v : E[u]) {
            if (v != p) {
                if (val >= hi) {
                    val = lo;
                    Sol.push_back({u, val});
                }

                ++val;
                dfs(v, u, val);
                Sol.push_back({u,val});
            }
        }

        if (p != -1 && val != beg-1) {
            Sol.push_back({u, beg-1});
        }
    }


    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        if (N == 1) {
            cout << "1\n1 0\n";
            return;
        }
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v; cin >> u >> v;
            --u; --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        dfs(0, -1, 0);

        cout << Sol.size() << '\n';
        for (pii sol: Sol) cout << sol.x+1 << ' ' << sol.y << '\n';
    }
};
