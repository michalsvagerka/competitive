#include "../l/lib.h"
 #include "../l/graph.h"

class ESugigmaTheShowdown {
public:

    void solve(istream& cin, ostream& cout) {
        int N, X, Y; cin >> N >> X >> Y;
        --X; --Y;

        vector<vector<int>> E(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }


        Tree T(N);
        for (int i = 0; i < N-1; ++i) {
            int u, v; cin >> u >> v; --u; --v;
                T.addEdge(u, v);
        }
        T.setRoot(Y);
        T.calcLA();

        vector<bool> Safe(N, false);
        for (int i = 0; i < N; ++i) {
            for (int j : E[i]) {
                int d = T.depth(i) + T.depth(j) - 2 * T.depth(T.lca(i, j));
                if (d >= 3) Safe[i] = true;
            }
        }

        vector<int> Q{X}, D(N, -1);
        D[X] = 0;
        int ans = T.depth(X);
        for (int q = 0; q < Q.size(); ++q) {
            int i = Q[q], d = D[i];
            for (int j : E[i]) {
                if (D[j] == -1 && d + 1 < T.depth(j)) {
                    if (Safe[j]) {
                        cout << "-1\n";
                        return;
                    } else {
                        D[j] = d + 1;
                        ans = max(ans, T.depth(j));
                        Q.push_back(j);
                    }
                }
            }
        }

        cout << 2*ans << '\n';
    }
};
