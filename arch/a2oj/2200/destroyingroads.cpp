#include "../../../l/lib.h"
// #include "../l/mod.h"

class destroyingroads {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<vector<int>> E(N);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        vector2<int> D(N,N,-1);
        for (int i = 0; i < N; ++i) {
            D[i][i] = 0;
            vector<int> Q{i};
            for (int j = 0; j < N; ++j) {
                int q = Q[j];
                for (int v:E[q]) {
                    if (D[i][v] == -1) {
                        D[i][v] = D[i][q] + 1;
                        Q.push_back(v);
                    }
                }
            }
        }

        int S1, T1, L1; cin >> S1 >> T1 >> L1; --S1; --T1;
        int S2, T2, L2; cin >> S2 >> T2 >> L2; --S2; --T2;
        int ans = M+1;
        if (D[S1][T1] <= L1 && D[S2][T2] <= L2) {
            ans = min(ans, D[S1][T1] + D[S2][T2]);
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int l1 = D[i][S1] + D[i][j] + D[j][T1];
                int l2 = D[i][S2] + D[i][j] + D[j][T2];
                if (l1 <= L1 && l2 <= L2) {
                    ans = min(ans, l1 + l2 - D[i][j]);
                }

                l2 = D[i][T2] + D[i][j] + D[j][S2];
                if (l1 <= L1 && l2 <= L2) {
                    ans = min(ans, l1 + l2 - D[i][j]);
                }
            }
        }

        cout << M - ans << endl;
    }
};
