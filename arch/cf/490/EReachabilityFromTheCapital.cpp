#include "../../../l/lib.h"
#include "../../../l/graph.h"

class EReachabilityFromTheCapital {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        int S; cin >> S; --S;
        vector<pii> E;
        vector<vector<int>> F(N);
        for (int i = 0; i < M; ++i) {
            int u, v; cin >> u >> v;
            --u; --v;
            E.emplace_back(u, v);
            F[u].push_back(v);
        }

        DirectedGraph G(N);
        for (pii e: E) G.addEdge(e.x, e.y);
        G.calcStronglyConnectedComponents();
        auto P = G.stronglyConnectedPermutation();

        vector<int> Q{S};
        vector<bool> V(N, false);
        V[S] = true;
        for (int q = 0; q < Q.size(); ++q) {
            int u = Q[q];
            for (int v : F[u]) {
                if (!V[v]) {
                    V[v] = true;
                    Q.push_back(v);
                }
            }
        }

        int ans = 0;
        for (int i = N-1; i >= 0; --i) {
            int j = P[i];
            if (!V[j]) {
                ans++;
                Q = {j};
                V[j] = true;
                for (int q = 0; q < Q.size(); ++q) {
                    int u = Q[q];
                    for (int v : F[u]) {
                        if (!V[v]) {
                            V[v] = true;
                            Q.push_back(v);
                        }
                    }
                }
            }
        }
        cout << ans << '\n';
    }
};
