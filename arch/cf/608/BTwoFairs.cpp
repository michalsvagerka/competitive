#include "../l/lib.h"
#include "../l/util.h"

class BTwoFairs {
public:
    int N, M, A, B;
    vector<vector<int>> E;
    
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            cin >> N >> M >> A >> B; --A; --B;
            E.clear(); E.resize(N);
            for (int i = 0; i < M; ++i) {
                int u, v;
                cin >> u >> v;
                --u;
                --v;
                E[u].push_back(v);
                E[v].push_back(u);
            }
            
            UnionFind UF(N);
            for (int i = 0; i < N; ++i) {
                for (int j : E[i]) {
                    if (i != A && i != B && j != A && j != B) {
                        UF.unite(i, j);
                    }
                }
            }

            vector<bool> MA(N, false), MB(N, false);
            vector<int> C(N, 0);
            for (int j : E[A]) if (j != B) MA[UF.find(j)] = true;
            for (int j : E[B]) if (j != A) MB[UF.find(j)] = true;
            for (int i = 0; i < N; ++i) C[UF.find(i)]++;
            int ma = 0, mb = 0;
            for (int i = 0; i < N; ++i) {
                if (MA[i] && !MB[i]) ma += C[i];
                if (MB[i] && !MA[i]) mb += C[i];
            }
            cout << ll(ma) * ll(mb) << '\n';
        }
    }
};
