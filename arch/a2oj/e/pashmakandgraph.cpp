#include "../../../l/lib.h"
// #include "../l/mod.h"

class pashmakandgraph {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        map<int, vector<pii>> E;
        for (int i = 0; i < M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            --u; --v;
            E[w].push_back({u,v});
        }

        vector<int> V(N, 0);
        for (auto&e:E) {
            vector<int> A(e.y.size());
            for (int i = 0; i < e.y.size(); ++i) {
                int v = e.y[i].x;
                A[i] = V[v]+1;
            }

            for (int i = 0; i < e.y.size(); ++i) {
                int w = e.y[i].y;
                V[w] = max(V[w], A[i]);
            }
        }

        cout << *max_element(V.begin(),V.end()) << endl;
    }
};
