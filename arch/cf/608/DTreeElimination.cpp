#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class DTreeElimination {
public:
    vector<vector<int>> E;
    int N;

    vector<FF> dfs(int u, int p) {
        vector<vector<FF>> Vals;
        int id = -1;
        for (int v: E[u]) {
            if (v == p) {
                id = Vals.size();
            } else {
                Vals.push_back(dfs(v,u));
            }
        }
        int M = Vals.size();
        vector<FF> PrefA(M+1, 1), SufB(M+1, 1);
        for (int i = 0; i < M; ++i) {
            PrefA[i+1] = PrefA[i] * (Vals[i][0] + Vals[i][2]);
            SufB[M-i-1] = SufB[M-i] * (Vals[M-i-1][2] + Vals[M-i-1][1]);
        }

        // 0 - B - bottom now
        // 1 - U - (up or up previously) and bottom not
        // 2 - D - bottom previously

        vector<FF> Ans(3, 0);
        for (int i = 0; i < M; ++i) {
            // the i-th says up
            FF val = PrefA[i] * Vals[i][1] * SufB[i+1];
            if (i < id) {
                Ans[2] += val;
            } else {
                Ans[1] += val;
            };
        }

        if (id != -1) {
            FF val = PrefA[id] * SufB[id];
            Ans[0] += val;
        }

        Ans[1] += PrefA[M];
        return Ans;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }
        auto s = dfs(0, -1);
        cout << s[1] << '\n';
    }
};
