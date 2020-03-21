#include "../l/lib.h"

int S[3000][3000];
int Dist[3000][3000];
ll Ans[3000][3000];

class CXenonsAttackOnTheGangs {
public:
    vector<vector<int>> E;
    int N;

    void dfs(int u, int p, int root) {
        S[root][u] = 1;
        for (int v : E[u]) {
            if (v != p) {
                dfs(v, u, root);
                S[root][u] += S[root][v];
            }
        }
    }

    void dfs2(int u, int p, int root, int dist) {
        Dist[root][u] = dist;
        for (int v : E[u]) {
            if (v != p) {
                dfs2(v, u, root, dist+1);


            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N-1; ++i) {
            int u,v; cin >> u >> v; --v; --u;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        for (int i = 0; i < N; ++i) {
            dfs(i, -1, i);
            dfs2(i, -1, i, 0);
        }

        vector<vector<pii>> Pair(N);
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                Pair[Dist[i][j]].push_back({i,j});
            }
        }
        for (pii p: Pair[1]) {
            int i = p.x, j = p.y;
            Ans[i][j] = Ans[j][i] = S[i][j] * S[j][i];
        }

        for (int q = 1; q < N; ++q) {
            for (pii p: Pair[q]) {
                int a = p.x, b = p.y;
                for (int c : E[a]) {
                    if (Dist[c][b] > Dist[a][b]) {
                        Ans[c][b] = Ans[b][c] = max(Ans[c][b], Ans[a][b] + S[b][c] * S[c][b]);
                    }
                }
                for (int d : E[b]) {
                    if (Dist[a][d] > Dist[a][b]) {
                        Ans[a][d] = Ans[d][a] = max(Ans[a][d], Ans[a][b] + S[d][a] * S[a][d]);
                    }
                }
            }
        }


        ll ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                ans = max(ans, Ans[i][j]);
            }
        }
        cout << ans << '\n';
    }
};
