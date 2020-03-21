#include "../l/lib.h"

class BShortestCycle {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N); cin >> A;
        vector<vector<int>> X(62);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < 62; ++j) {
                if (A[i]&1LL<<j) X[j].push_back(i);
            }
        }

        for (int i = 0; i < 62; ++i) {
            if (X[i].size() >= 3) {
                cout << "3\n";
                return;
            }
        }

        map<int, set<int>> E;
        for (int i = 0; i < 62; ++i) {
            if (X[i].size() == 2) {
                ll a = X[i][0], b = X[i][1];
                if (a != b) {
                    E[a].insert(b);
                    E[b].insert(a);
                }
            }
        }
        
        map<int, int> F;
        for (auto e: E) {
            int f = F.size();
            F[e.x] = f;
        }
        
        vector<vector<int>> G(F.size());
        for (auto e: E) {
            for (auto f: e.y) {
                G[F[e.x]].push_back(F[f]);
            }
        }

        int ans = 80;
        for (int i = 0; i < F.size(); ++i) {
            vector<int> D(F.size(), 100), P(F.size(), -1);
            D[i] = 0;
            vector<int> Q{i};
            for (int q = 0; q < Q.size(); ++q) {
                int u = Q[q];
                for (int v : G[u]) {
                    if (v == P[u]) {
                    } else if (D[v] != 100) {
                        ans = min(ans, D[v] + D[u] + 1);
                    } else {
                        P[v] = u;
                        D[v] = D[u] + 1;
                        Q.push_back(v);
                    }
                }
            }
        }
        
        if (ans == 80) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
        
        
    }
};
