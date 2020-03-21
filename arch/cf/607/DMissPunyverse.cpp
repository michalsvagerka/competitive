#include "../l/lib.h"

class DMissPunyverse {
public:
    int N, M;
    vector<vector<int>> E;
    vector<int> D;
    vector<vector<pair<int,ll>>> F;

    void solve(int u, int p) {
        vector<pair<int,ll>> G{{0, D[u]}};
        for (int v: E[u]) if (v != p) {
            solve(v, u);
            vector<pair<int,ll>> H(G.size() + F[v].size() - 1, {0, ll(-1e18)});
            for (int i = 0; i < G.size(); ++i) {
                for (int j = 0; j < F[v].size(); ++j) {
                    H[i+j] = max(H[i+j], {G[i].x+F[v][j].x, G[i].y+F[v][j].y});
                }
            }
            swap(G,H);
        }
        F[u].assign(G.size()+1, {0, ll(-1e18)});
        for (int i = 0; i < G.size(); ++i) {
            F[u][i] = max(F[u][i], G[i]);
            F[u][i+1] = max(F[u][i], {G[i].x + (G[i].y > 0), 0LL});
        }
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            cin >> N >> M;
            vector<int> B(N), W(N);
            D.resize(N);
            cin >> B >> W;
            for (int i = 0; i < N; ++i) D[i] = W[i] - B[i];

            if (N == 1) {
                cout << (D[0] > 0) << '\n';
                continue;
            }

            E.clear();
            E.resize(N);
            for (int i = 0; i < N - 1; ++i) {
                int u, v;
                cin >> u >> v;
                --u;
                --v;
                E[u].push_back(v);
                E[v].push_back(u);
            }

            F.clear();
            F.resize(N);
            solve(0, -1);
            cout << F[0][M-1].x + (F[0][M-1].y > 0) << '\n';
        }
    }
};
