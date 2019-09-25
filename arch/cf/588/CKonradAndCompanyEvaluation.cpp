#include "../l/lib.h"

class CKonradAndCompanyEvaluation {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        int M; cin >> M;
        vector<vector<int>> E(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        vector<vector<int>> LO(N);
        auto get = [&](int i) { return ll(LO[i].size()) * ll(E[i].size() - LO[i].size()); };
        ll cur = 0;
        for (int i = 0; i < N; ++i) {
            for (int j : E[i]) {
                if (i < j) LO[i].push_back(j);
            }
            cur += get(i);
        }
        cout << cur << endl;

        int Q; cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int u; cin >> u; --u;
            cur -= get(u);
            for (int v: LO[u]) {
                cur -= get(v);
                LO[v].push_back(u);
                cur += get(v);
            }
            LO[u].clear();
            cur += get(u);
            cout << cur << '\n';
        }
    }
};
