#include "../../../l/lib.h"

class FBerlandAndTheShortestPaths {
public:
    int N, M, K;
    vector<pii> E;
    vector<vector<pii>> F;
    vector<int> D, Q;
    vector<vector<int>> Prev;


    void solve(istream& cin, ostream& cout) {
        cin >> N >> M >> K;
        E.resize(M); cin >> E;
        F.resize(N);
        for (int i = 0; i < M; ++i) {
            pii&e = E[i];
            e.x--; e.y--;
            F[e.x].emplace_back(e.y, i);
            F[e.y].emplace_back(e.x, i);
        }

        D.assign(N, N);
        D[0] = 0;
        Prev.resize(N);
        Q = {0};
        for (int q = 0; q < N; ++q) {
            int u = Q[q];
            for (pii v: F[u]) {
                if (D[v.x] == D[u] + 1) {
                    Prev[v.x].push_back(v.y);
                } else if (D[v.x] > D[u] + 1) {
                    Q.push_back(v.x);
                    D[v.x] = D[u] + 1;
                    Prev[v.x] = {v.y};
                }
            }
        }

        vector<string> Ans;
        for (int i = 0; i < K; ++i) {
            string S(M, '0');
            int k = i;
            for (int j = 1; j < N; ++j) {
                int s = Prev[j].size();
                S[Prev[j][k%s]] = '1';
                k /= s;
            }
            if (k) break;
            Ans.push_back(S);
        }

        cout << Ans.size() << '\n';
        for (string ans: Ans) cout << ans << '\n';
    }
};
