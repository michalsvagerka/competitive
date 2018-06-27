#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class ostapandtree {
public:
    int N, K;
    vector<vector<int>> E;
    vector3<FieldMod> D;

    void dfs(int u, int p) {
        vector2<FieldMod> W(K+1,K+2,0);
        W[0][K+1] = 1;

        for (int v:E[u]) {
            if (v!=p) {
                dfs(v, u);
                vector2<FieldMod> S(K+1,K+2,0);
                for (int s = 0; s <= K; ++s) {
                    for (int t = 0; t <= K+1; ++t) {
                        for (int a = 0; a <= K; ++a) {
                            for (int b = 0; b <= K+1; ++b) {
                                int l1 = s+b <= K ? 0 : s;
                                int l2 = t+a <= K ? 0 : a;
                                int l = max(l1, l2);
                                int k = min(t, b);
                                S[l][k] += W[s][t] * D[v][a][b];
                            }
                        }
                    }
                }
                swap(W,S);
            }
        }

        for (int s = 0; s <= K; ++s) {
            for (int t = 0; t <= K+1; ++t) {
                // white
                if (s == 0 && t <= K) {
                    D[u][0][t+1] += W[s][t];
                } else if (s != K) {
                    D[u][s+1][min(t+1, K+1)] += W[s][t];
                }

                // black
                D[u][0][1] += W[s][t];
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N >> K;
        E.resize(N);
        D = vector3<FieldMod>(N,K+1,K+2,0);
        if (K == 0) {
            cout << 1 << endl;
            return;
        }

        for (int i = 0; i < N - 1; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        dfs(0, -1);
        FieldMod ans = 0;
        for (int i = 0; i <= K+1; ++i) {
            ans += D[0][0][i];
        }

        cout << ans << endl;
    }
};
