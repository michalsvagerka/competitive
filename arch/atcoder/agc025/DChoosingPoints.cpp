#include "../l/lib.h"
#include "../l/random.h"

class DChoosingPoints {
public:
    vector<bool> V, P;
    void partition(int u, const vector<vector<int>> &E, bool p) {
        if (V[u]) return;
        V[u] = true;
        P[u] = p;
        for (int v : E[u]) partition(v, E, !p);
    }

    void solve(istream& cin, ostream& cout) {
        int N, D1, D2;
        cin >> N >> D1 >> D2;
        vector<pii> Ans;

        vector<int> PP(4*N*N, 0);
        for (int D:{D1, D2}) {
            vector<pii> Q;
            for (int i = -2*N + 1; i < 2*N; ++i) {
                for (int j = -2*N + 1; j < 2*N; ++j) {
                    if (i * i + j * j == D) Q.push_back({i, j});
                }
            }

            vector<vector<int>> E(4 * N * N);
            for (int i = 0; i < 2*N; ++i) {
                for (int j = 0; j < 2*N; ++j) {
                    for (pii q : Q) {
                        int xx = i + q.x, yy = j + q.y;
                        if (0 <= xx && xx < 2 * N && 0 <= yy && yy < 2 * N) {
                            E[i*2*N+j].push_back(xx*2*N+yy);
                        }
                    }
                }
            }

            V.assign(4*N*N, false);
            P.resize(4*N*N);
            for (int i = 0; i < 4*N*N; ++i) {
                partition(i, E, true);
                PP[i] = 2*PP[i] + P[i];
            }
        }

        vector<vector<int>> S(4);
        for (int i = 0; i < 4*N*N; ++i) S[PP[i]].push_back(i);

        for (int i = 0; i < 4; ++i) {
            if (S[i].size() >= N*N) {
                for (int s:S[i]) Ans.push_back({s%(2*N),s/(2*N)});
                Ans.resize(N*N);
                for (pii ans:Ans) cout << ans << '\n';
                return;
            }
        }
    }
};
