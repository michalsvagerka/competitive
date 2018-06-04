#include "../../../l/lib.h"
// #include "../l/mod.h"

class flawedflow {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<vector<int>> E(N);
        vector<pair<pii,int>> F(M);
        vector<int> D(M, -1), Z(N, 0);

        for (int i = 0; i < M; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            --u;
            --v;
            E[u].push_back(i);
            E[v].push_back(i);
            F[i] = {{u,v},c};
            Z[u] += c;
            Z[v] += c;
        }

        Z[N-1] += Z[0];
        Z[0] = 0;
        vector<int> Q{0};
        for (int q = 0; q < Q.size(); ++q) {
            int u = Q[q];
            for (int j : E[u]) {
                if (D[j] == -1) {
                    D[j] = (F[j].x.x != u);
                    int v = F[j].x.x + F[j].x.y - u;
                    Z[v] -= 2*F[j].y;
                    if (Z[v] == 0) {
                        Q.push_back(v);
                    }
                }
            }
        }


        for (int d:D) cout << d << '\n';
    }
};
