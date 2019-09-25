#include "../l/lib.h"

class GraphsAsAService {
public:
    int T = 0;
    void solve(istream& cin, ostream& cout) {
        cout << "Case #" << ++T << ": ";
        int N, M; cin >> N >> M;
        vector<pair<pii, int>> E;
        vector2<int> D(N, N, 1e9);
        for (int i = 0; i < M; ++i) {
            int u, v, c; cin >> u >> v >> c;
            --u; --v;
            E.push_back({{u,v}, c});
            D[u][v] = D[v][u] = c;
        }
        for (int i = 0; i < N; ++i) {
            D[i][i] = 0;
        }

        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
                }
            }
        }
        
        for (auto e: E) {
            if (D[e.x.x][e.x.y] != e.y) {
                cout << "Impossible\n";
                return;
            }
        }
        
        cout << E.size() << '\n';
        for (auto e: E) {
            cout << e.x.x + 1 << ' ' << e.x.y + 1 << ' ' << e.y << '\n';
        }
    }
};
