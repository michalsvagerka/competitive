#include "../l/lib.h"

class BEdgeWeightAssignment {
public:
    int N; 
    vector<vector<int>> E;
    vector<bool> P;

    void bipartite(int u, int p, bool par) {
        P[u] = par;
        for (int v : E[u]) {
            if (v != p) {
                bipartite(v, u, !par);
            }
        }
    }
    
    void solve(istream& cin, ostream& cout) {
        cin >> N;
        E.resize(N);
        for (int i = 0; i < N-1; ++i) {
            int u, v; cin >> u >> v;
            --u; --v;
            E[u].push_back(v);
            E[v].push_back(u);
        }

        P.resize(N);
        for (int i = 0; i < N; ++i) {
            if (E[i].size() == 1) {
                bipartite(i, -1, true);
                break;
            }
        }

        bool bip = true;
        for (int i = 0; i < N; ++i) {
            if (E[i].size() == 1) {
                bip &= P[i];
            }
        }

        int lo = bip ? 1 : 3;
        int hi = N-1;
        for (int i = 0; i < N; ++i) {
            int leafs = 0;
            for (int j : E[i]) {
                leafs += E[j].size() == 1;
            }
            hi -= max(leafs-1,0);
        }
        cout << lo << ' ' << hi << endl;

    }
};
