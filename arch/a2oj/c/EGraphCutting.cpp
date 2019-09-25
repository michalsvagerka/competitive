#include "../l/lib.h"

class EGraphCutting {
public:
    vector<vector<int>> E;
    vector<vector<int>> Ans;
    set<pii> U;
    vector<bool> V;
    vector<int> P;
    
    bool dfs(int u, int p) {
        V[u] = true;
        int w = -1;
        for (int v : E[u]) {
            if (U.count({v,u}) == 0 && U.count({u,v}) == 0 && v != p && (V[v] || !dfs(v, u))) {
                if (w == -1) {
                    w = v;
                } else {
                    U.insert({w,u});
                    U.insert({v,u});
                    Ans.push_back({w+1, u+1, v+1});
                    w = -1;
                }
            }
        }

        if (w != -1) {
            U.insert({w,u});
            U.insert({p,u});
            Ans.push_back({w+1, u+1, p+1});
            return true;
        } else {
            return false;
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        if (M % 2 == 1) {
            cout << "No solution\n";
            return;
        }

        V.assign(N, false);
        P.assign(N, -1);
        E.resize(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        dfs(0, -1);
        for (auto&p: Ans) cout << p;
    }
};
