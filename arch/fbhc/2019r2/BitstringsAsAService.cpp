#include "../l/lib.h"
#include "../l/random.h"

class BitstringsAsAService {
public:
    vector<vector<bool>> E;
    vector<int> V;
    int N;

    void dfs(int u, int c) {
        if (V[u] != -1) return;
        V[u] = c;
        for (int v = 0; v < N; ++v) if (E[u][v] && V[v] == -1) dfs(v, c);
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 1; t <= T; ++t) {
            int M;
            cin >> N >> M;
            vector<pii> C(M); cin >> C;
            for (pii&c:C) { --c.x; --c.y; }
            E = vector2<bool>(N, N, false);
            V.assign(N, -1);
            for (pii c:C) {
                for (int i = c.x; i <= c.y; ++i) {
                    int j = c.x+c.y-i;
                    if (E[i][j]) break;
                    E[i][j] = E[j][i] = true;
                }
            }
            int comp = 0;
            for (int i = 0; i < N; ++i) if (V[i] == -1) dfs(i, comp++);
            vector<int> CNT(comp, 0);
            for (int i = 0; i < N; ++i) CNT[V[i]]++;
            vector2<bool> D(comp+1, N+1, false);
            D[0][0] = true;
            for (int i = 0; i < comp; ++i) {
                for (int j = 0; j <= N; ++j) {
                    if (D[i][j]) {
                        D[i+1][j] = D[i+1][j+CNT[i]] = true;
                    }
                }
            }

            pii best = {N+1, -1};
            for (int i = 0; i <= N; ++i) {
                if (D[comp][i]) best = min(best, {abs(N-2*i), i});
            }

            vector<bool> P(comp, false);
            int s = best.y;
            for (int i = comp-1; i >= 0; --i) {
                if (!D[i][s]) {
                    P[i] = true;
                    s -= CNT[i];
                }
            }
            string S(N, '0');
            for (int i = 0; i < N; ++i) if (P[V[i]]) S[i] = '1';

            cout << "Case #" << t << ": " << S << '\n';
        }
    }
};
