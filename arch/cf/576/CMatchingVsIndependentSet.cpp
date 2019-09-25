#include "../l/lib.h"

class CMatchingVsIndependentSet {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N, M; cin >> N >> M;
            vector<vector<pii>> E(3 * N);
            for (int i = 0; i < M; ++i) {
                int u, v;
                cin >> u >> v;
                --u;
                --v;
                E[u].push_back({v,i});
                E[v].push_back({u,i});
            }

            vector<bool> U(3*N, false);
            vector<int> Match;
            vector<int> Indep;
            for (int i = 0; i < 3*N; ++i) {
                if (!U[i]) {
                    for (pii v : E[i]) {
                        if (!U[v.x]) {
                            Match.push_back(v.y+1);
                            U[i] = U[v.x] = true;
                            break;
                        }
                    }
                    if (!U[i]) {
                        U[i] = true;
                        Indep.push_back(i+1);
                    }
                }
            }
            if (Indep.size() >= N) {
                Indep.resize(N);
                cout << "IndSet\n" << Indep;
            } else {
                Match.resize(N);
                cout << "Matching\n" << Match; 
            }
        }
    }
};
