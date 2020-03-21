#include "../l/lib.h"
#include "../l/util.h"

class B01MST {
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

        UnionFind UF(N);
        auto process = [&](int i) {
            vector<bool> U(N, false);
            for (int j: E[i]) U[j] = true;
            U[i] = true;
            for (int j = 0; j < N; ++j) {
                if (!U[j]) UF.unite(i, j);
            }
        };

        vector<int> Lodeg;
        for (int i = 0; i < N; ++i) {
            if (E[i].size() >= (N-2)/3) process(i);
            else Lodeg.push_back(i);
        }

        if (!Lodeg.empty()) {
            for (int i: Lodeg) {
                UF.unite(i, Lodeg[0]);
            }
        }

        cout << UF.comp - 1 << '\n';
    }
};
