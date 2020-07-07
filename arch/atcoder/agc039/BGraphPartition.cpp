#include "../../../l/lib.h"

class BGraphPartition {
public:
    int N;
    vector<bool> Vis, Par;
    bool is_bip(const vector<vector<int>> &D, int u, bool p) {
        if (Vis[u]) return Par[u] == p;
        Vis[u] = true;
        Par[u] = p;
        for (int i = 0; i < N; ++i) if (D[u][i] && !is_bip(D, i, !p)) return false;
        return true;
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        vector2<int> V(N, N);
        for (int i = 0; i < N; ++i) {
            string S; cin >> S;
            for (int j = 0; j < N; ++j) {
                V[i][j] = (S[j] == '1');
            }
        }

        Vis.assign(N, false); Par.assign(N, false);
        if (!is_bip(V, 0, true)) {
            cout << "-1\n";
            return;
        }

        int mx = 0;
        for (int i = 0; i < N; ++i) {
            vector<int> D(N, N), Q{i};
            D[i] = 0;
            for (int q = 0; q < Q.size(); ++q) {
                int j = Q[q];
                for (int k = 0; k < N; ++k) {
                    if (V[j][k] == 1 && D[k] == N) {
                        D[k] = D[j]+1;
                        Q.push_back(k);
                    }
                }
            }
            mx = max(mx, *max_element(D.begin(),D.end()));
        }

        cout << mx + 1 << endl;
    }
};
