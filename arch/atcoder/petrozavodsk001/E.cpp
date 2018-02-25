#include "../../../l/lib.h"
// #include "../l/mod.h"

class E {
public:
    int N;
    vector<vector<int>> E;

    int dfs(int u, int p, bool&above) {
        above = false;
        vector<int> Q;
        for (int v:E[u]) {
            if (v != p) {
                bool nA;
                Q.push_back(dfs(v,u, nA));
                above |= nA;
            }
        }
        sort(Q.begin(),Q.end());

        if (Q.size() > 2 || (Q.size() == 2 && Q[0] > 0)) {
            above = false;
        }

        if (Q.size() == 2 && Q[0] == 0) {
            above = true;
        }

        int q = 0;
        for (int i = 0; i < Q.size(); ++i) q += Q[i] + (i > 0 && Q[i] == 0);
        return q;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;

        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int a,b; cin >> a >> b;
            E[a].push_back(b);
            E[b].push_back(a);
        }

        int mx = 0;
        for (int i = 0; i < N; ++i) {
            mx = max(mx, int(E[i].size()));
        }

        if (mx < 3) {
            cout << 1 << endl;
            return;
        }

        for (int i = 0; i < N; ++i) {
            if (E[i].size() > 1) {
                bool above;
                int ans = dfs(i, -1, above);
                ans += (above);
                cout << ans << endl;
                return;
            }
        }

    }
};
